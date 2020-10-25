// Copyright Epic Games, Inc. All Rights Reserved.

#include "HackAndSlashGameModeBase.h"
#include "HackAndSlashPlayerController.h"

AHackAndSlashGameModeBase::AHackAndSlashGameModeBase()
{
	PlayerControllerClass = AHackAndSlashPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnBPClass(TEXT("/Game/Character/HackAndSlashCharacter"));
	if (DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}
}