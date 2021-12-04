// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Health Component|Health Bar", meta = (BindWidgetOptional))
	class UProgressBar* HealthBar;

public:
	virtual void NativeConstruct() override;
	void SetHealthValue(float Health);

	UFUNCTION()
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetPlayerHealthPercent() const;

private:
	float HealthValue = 0.0f;
};