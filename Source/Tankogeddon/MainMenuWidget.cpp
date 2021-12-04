// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);
	}

	if (Resolution1)
	{
		Resolution1->OnClicked.AddDynamic(this, &UMainMenuWidget::OnResolution1Clicked);
	}

	if (Resolution2)
	{
		Resolution2->OnClicked.AddDynamic(this, &UMainMenuWidget::OnResolution2Clicked);
	}

	if (Resolution3)
	{
		Resolution3->OnClicked.AddDynamic(this, &UMainMenuWidget::OnResolution3Clicked);
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnReturnClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	UGameplayStatics::SetGamePaused(this, false);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void UMainMenuWidget::OnResolution1Clicked()
{
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	GameSettings->SetScreenResolution(FIntPoint(960, 600));
	GameSettings->ApplySettings(true);
}

void UMainMenuWidget::OnResolution2Clicked()
{
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	GameSettings->SetScreenResolution(FIntPoint(1280, 800));
	GameSettings->ApplySettings(true);
}

void UMainMenuWidget::OnResolution3Clicked()
{
	UGameUserSettings* GameSettings = GEngine->GetGameUserSettings();
	GameSettings->SetScreenResolution(FIntPoint(1440, 900));
	GameSettings->ApplySettings(true);
}

void UMainMenuWidget::OnQuitClicked()
{
	APlayerController* TankPawnPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), TankPawnPlayer, EQuitPreference::Quit, true);
}