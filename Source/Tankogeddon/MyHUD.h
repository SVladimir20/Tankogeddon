// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */

UENUM()
enum class EWidgetID : uint8
{
	None,
	MainMenu,
	GameOverScreen
};

UCLASS()
class TANKOGEDDON_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClases;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* CurrentWidget;

	EWidgetID CurrentWidgetID;

public:
	void BeginPlay() override;

	UUserWidget* UseWidget(EWidgetID widgetID, bool RemovePrevious = true, int32 ZOrder = 0);

	UUserWidget* GetCurrentWidget();

	void RemoveCurrentWidgetFromViewport();
	UUserWidget* AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);
};