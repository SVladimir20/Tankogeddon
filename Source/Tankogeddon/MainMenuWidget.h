// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Main Menu|Play Game", meta = (BindWidgetOptional))
	class UButton* PlayButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Main Menu|Options", meta = (BindWidgetOptional))
	class UButton* OptionsButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Options Menu|960x600", meta = (BindWidgetOptional))
	class UButton* Resolution1;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Options Menu|1280x800", meta = (BindWidgetOptional))
	class UButton* Resolution2;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Options Menu|1440x900", meta = (BindWidgetOptional))
	class UButton* Resolution3;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Options Menu|Return", meta = (BindWidgetOptional))
	class UButton* ReturnButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Main Menu|Quit", meta = (BindWidgetOptional))
	class UButton* QuitButton;

	UFUNCTION(Category = "Main Menu|Play Game")
	void OnPlayClicked();
	UFUNCTION(Category = "Main Menu|Options")
	void OnOptionsClicked() {}
	UFUNCTION(Category = "Options Menu|960x600")
	void OnResolution1Clicked();
	UFUNCTION(Category = "Options Menu|1280x800")
	void OnResolution2Clicked();
	UFUNCTION(Category = "Options Menu|1440x900")
	void OnResolution3Clicked();
	UFUNCTION(Category = "Options Menu|Return")
	void OnReturnClicked() {}
	UFUNCTION(Category = "Main Menu|Quit")
	void OnQuitClicked();
};