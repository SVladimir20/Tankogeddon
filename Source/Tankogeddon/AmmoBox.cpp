// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "TankPawn.h"
#include "Cannon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	Mesh->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

void AAmmoBox::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* PlayerPawn = Cast<ATankPawn>(OtherActor);
	ACannon* Cannon = Cast<ACannon>(PlayerPawn->FirstCannonClass);
	if (PlayerPawn && CannonClass)
	{
		UE_LOG(LogTemp, Display, TEXT("Picked up Tracer AmmoBox"));
		PlayerPawn->SetupCannon(CannonClass);
		Destroy();
	}
	else if (PlayerPawn && !CannonClass)
	{
		UE_LOG(LogTemp, Display, TEXT("Picked up Projectile AmmoBox"));
		PlayerPawn->Ammunition(Resupply);
		Destroy();
	}
}