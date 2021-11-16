// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Zadanie4GameMode.h"
#include "Zadanie4Character.h"
#include "UObject/ConstructorHelpers.h"

AZadanie4GameMode::AZadanie4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
