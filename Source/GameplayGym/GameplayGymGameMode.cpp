// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayGymGameMode.h"
#include "GameplayGymCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameplayGymGameMode::AGameplayGymGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
