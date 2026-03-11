// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDW_Technical_TestGameMode.h"
#include "TDW_Technical_TestPlayerController.h"
#include "TDW_Technical_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDW_Technical_TestGameMode::ATDW_Technical_TestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATDW_Technical_TestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}