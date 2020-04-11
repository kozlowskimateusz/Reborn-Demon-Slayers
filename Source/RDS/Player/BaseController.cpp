// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

ABaseController::ABaseController()
{

}


void ABaseController::OptionsWidget(bool bPause, bool bShowCursor, TEnumAsByte<InputOptions> InputOption)
{
	SetPause(bPause);
	bShowMouseCursor = bShowCursor;

	if (InputOption == InputModeGameOnly)
	{
		SetInputMode(FInputModeGameOnly());
	}
	else if (InputOption == InputModeUIOnly)
	{
		SetInputMode(FInputModeUIOnly());
	}
	else if (InputOption == InputModeGameAndUI)
	{
		SetInputMode(FInputModeGameAndUI());
	}
}
