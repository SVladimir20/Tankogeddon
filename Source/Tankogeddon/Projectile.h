// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float FireRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics")
	float Mass = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics|Movement")
	float ExplosionRange = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics|Movement")
	float ExplosionImpulse = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics|Mortire")
	bool bPhysicsProjectile = false;

public:
	AProjectile();

	virtual void Start();
	virtual void Stop();
	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION()
		virtual void OnMeshHit(class UPrimitiveComponent* HittedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult);

private:
	FVector StartPosition;
};