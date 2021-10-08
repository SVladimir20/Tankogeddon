// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    class UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    class UArrowComponent* ProjectileSpawnPoint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireRate = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireRange = 1000.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireDamage = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    ECannonType Type = ECannonType::FireProjectile;

    int32 MaxAmmo = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1), Category = "Fire params")
		int32 NumShotsInSeries = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "NumShotsInSeries > 1", EditConditionHides), Category = "Fire params")
		float SeriesLength = 1.f;

private:
    FTimerHandle ReloadTimerHandle;
    FTimerHandle SeriesTimerHandle;
    bool bIsReadyToFire = false;

public:
    ACannon();

    void Fire();

	void FireSpecial();

    bool IsReadyToFire();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

    void Reload();
    void Shot();

    int32 TotalAmmo = 0;
    int32 ShotsLeft = 0;
};