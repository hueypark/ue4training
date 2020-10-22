// Copyright Epic Games, Inc. All Rights Reserved.

#include "HackAndSlashGameMode.h"
#include "HackAndSlashPlayerController.h"
#include "HackAndSlashCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHackAndSlashGameMode::AHackAndSlashGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHackAndSlashPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}