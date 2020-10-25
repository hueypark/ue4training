// Copyright Epic Games, Inc. All Rights Reserved.

#include "HackAndSlashGameModeBase.h"

AHackAndSlashGameModeBase::AHackAndSlashGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnBPClass(TEXT("/Game/Character/HackAndSlashCharacter"));
	if (DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}
}