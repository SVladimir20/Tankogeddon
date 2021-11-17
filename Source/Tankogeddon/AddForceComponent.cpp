// Fill out your copyright notice in the Description page of Project Settings.


#include "AddForceComponent.h"
#include "Logging/LogMacros.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <Sound/SoundBase.h>

// Sets default values for this component's properties
UAddForceComponent::UAddForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAddForceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	MeshStartPosition = MeshComp->GetComponentLocation();
}

// Called every frame
void UAddForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector UP = this->GetUpVector();

	MeshComp->AddForce(UP * Force * MeshComp->GetMass());

	if (FVector::Distance(MeshComp->GetComponentLocation(), MeshStartPosition) > FlightHeight)
	{
		MeshComp->DestroyComponent();
	}
}