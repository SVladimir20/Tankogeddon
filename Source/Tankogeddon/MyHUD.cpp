// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, nullptr, EMouseLockMode::DoNotLock, false);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

UUserWidget* AMyHUD::GetCurrentWidget()
{
	return CurrentWidget;
}

void AMyHUD::RemoveCurrentWidgetFromViewport()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;

		CurrentWidgetID = EWidgetID::None;
	}
}

UUserWidget* AMyHUD::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder /*= 0*/)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}

	return CurrentWidget;
}

UUserWidget* AMyHUD::UseWidget(EWidgetID widgetID, bool RemovePrevious, int32 ZOrder)
{
	if (CurrentWidgetID == widgetID)
	{
		return CurrentWidget;
	}

	if (RemovePrevious)
	{
		RemoveCurrentWidgetFromViewport();
	}

	TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClases.FindRef(widgetID);
	if (WidgetClassToUse.Get())
	{
		CurrentWidgetID = widgetID;
		return AddWidgetToViewportByClass(WidgetClassToUse, ZOrder);
	}

	return nullptr;
}