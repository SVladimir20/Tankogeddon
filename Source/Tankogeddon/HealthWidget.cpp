// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/ProgressBar.h"
#include "TankPawn.h"

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HealthBar->PercentDelegate.BindUFunction(this, FName("GetHealth"));
	HealthBar->SynchronizeProperties();
}

void UHealthWidget::SetHealthValue(float Health)
{
	HealthValue = Health;
}

float UHealthWidget::GetHealth() const
{
	return HealthValue;
}

float UHealthWidget::GetPlayerHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
	{
		return 0;
	}
	const auto PlayerTank = Cast<ATankPawn>(Player);
	return PlayerTank->GetHealthValue();
}