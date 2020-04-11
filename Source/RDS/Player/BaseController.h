// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"


UENUM(BlueprintType)
enum InputOptions
{
	InputModeGameOnly,
	InputModeGameAndUI,
	InputModeUIOnly,
};


/**
 * 
 */
UCLASS()
class RDS_API ABaseController : public APlayerController
{
	GENERATED_BODY()
public:

	ABaseController();

	UFUNCTION(BlueprintCallable, Category = "Widgets|Options")
	void OptionsWidget(bool bPause, bool bShowCursor, TEnumAsByte<InputOptions> InputOption);
};
