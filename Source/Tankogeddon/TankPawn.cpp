// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Math/UnrealMathUtility.h"
#include "Tankogeddon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "HealthWidget.h"
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <Sound/SoundBase.h>
#include "Components/WidgetComponent.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
    RootComponent = BodyMesh;

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
    TurretMesh->SetupAttachment(BodyMesh);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
    SpringArm->SetupAttachment(BodyMesh);
    SpringArm->bDoCollisionTest = false;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    CannonSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
    CannonSpawnPoint->SetupAttachment(TurretMesh);

    HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
    HitCollider->SetupAttachment(BodyMesh);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
    HealthComponent->OnDie.AddDynamic(this, &ATankPawn::OnDie);
    HealthComponent->OnHealthChanged.AddDynamic(this, &ATankPawn::OnHealthChanged);

    DyingVisibleEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Dying Visible Effect"));
    DyingAudioEffect = CreateDefaultSubobject<USoundBase>(TEXT("Dying Audio Effect"));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
    HealthWidgetComponent->SetupAttachment(RootComponent);
}

int32 ATankPawn::GetScores() const
{
    return DestructionScores;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
    SetupCannon(DefaultCannonClass);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CurrentMoveForwardAxis = FMath::FInterpTo(CurrentMoveForwardAxis, TargetMoveForwardAxis, DeltaTime, MovementSmootheness);
    FVector MoveVector = GetActorForwardVector() * CurrentMoveForwardAxis;
    FVector NewActorLocation = GetActorLocation() + MoveVector * MoveSpeed * DeltaTime;
    SetActorLocation(NewActorLocation, true);
    
    CurrentRotateRightAxis = FMath::FInterpTo(CurrentRotateRightAxis, TargetRotateRightAxis, DeltaTime, RotationSmootheness);
    float Rotation = GetActorRotation().Yaw + CurrentRotateRightAxis * RotationSpeed * DeltaTime;
    SetActorRotation(FRotator(0.f, Rotation, 0.f));

    UE_LOG(LogTankogeddon, Verbose, TEXT("CurrentRotateRightAxis: %f"), CurrentRotateRightAxis);

    if (!bIsTurretTargetSet)
    {
        TurretTargetDirection = TurretTargetDirection.RotateAngleAxis(TurretRotationSmootheness * DeltaTime * TurretRotationAxis, FVector::UpVector);
        TurretTargetPosition = GetActorLocation() + TurretTargetDirection;
    }

    FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TurretTargetPosition);
    FRotator CurrentRotation = TurretMesh->GetComponentRotation();
    TargetRotation.Roll = CurrentRotation.Roll;
    TargetRotation.Pitch = CurrentRotation.Pitch;
    TurretMesh->SetWorldRotation(FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, TurretRotationSmootheness));

	if (UHealthWidget* HealthWidget = Cast<UHealthWidget>(HealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->SetHealthValue(GetHealthValue());
		UE_LOG(LogTemp, Warning, TEXT("Check Health"));
	}
}

void ATankPawn::MoveForward(float InAxisValue)
{
    TargetMoveForwardAxis = InAxisValue;
}

void ATankPawn::RotateRight(float InAxisValue)
{
    TargetRotateRightAxis = InAxisValue;
}

void ATankPawn::SetTurretTargetPosition(const FVector& TargetPosition)
{
    TurretTargetPosition = TargetPosition;
    bIsTurretTargetSet = true;
}

void ATankPawn::SetTurretRotationAxis(float AxisValue)
{
    TurretRotationAxis = AxisValue;
    TurretTargetDirection = TurretTargetPosition - GetActorLocation();
    bIsTurretTargetSet = false;
}

void ATankPawn::Fire()
{
    if (ActiveCannon)
    {
        ActiveCannon->Fire();
    }
}

void ATankPawn::FireSpecial()
{
    if (ActiveCannon)
    {
        ActiveCannon->FireSpecial();
    }
}

void ATankPawn::SetupCannon(TSubclassOf<class ACannon> InCannonClass)
{
    if (ActiveCannon)
    {
        ActiveCannon->Destroy();
    }

    if (InCannonClass)
    {
        FActorSpawnParameters Params;
        Params.Instigator = this;
        Params.Owner = this;
        ActiveCannon = GetWorld()->SpawnActor<ACannon>(InCannonClass, Params);
        ActiveCannon->AttachToComponent(CannonSpawnPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    }
}

void ATankPawn::CycleCannon()
{
    Swap(ActiveCannon, InactiveCannon);
    if (ActiveCannon)
    {
        ActiveCannon->SetVisibility(true);
    }

    if (InactiveCannon)
    {
        InactiveCannon->SetVisibility(false);
    }
}

ACannon* ATankPawn::GetActiveCannon() const
{
    return ActiveCannon;
}

FVector ATankPawn::GetTurretForwardVector()
{
    return TurretMesh->GetForwardVector();
}

void ATankPawn::TakeDamage(const FDamageData& DamageData)
{
    HealthComponent->TakeDamage(DamageData);
}

void ATankPawn::OnHealthChanged_Implementation(float Damage)
{
    UE_LOG(LogTankogeddon, Log, TEXT("Tank %s taken damage:%f "), *GetName(), Damage);
}

void ATankPawn::OnDie_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DyingVisibleEffect, GetActorLocation(), GetActorRotation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DyingAudioEffect, GetActorLocation(), GetActorRotation());
	if (ActiveCannon)
	{
        ActiveCannon->Destroy();
	}
	Destroy();
}