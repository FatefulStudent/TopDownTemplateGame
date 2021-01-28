// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownTemplateGameGameMode.h"
#include "TopDownTemplateGamePlayerController.h"
#include "TopDownTemplateGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownTemplateGameGameMode::ATopDownTemplateGameGameMode()
{
	PlayerControllerClass = ATopDownTemplateGamePlayerController::StaticClass();
	DefaultPawnClass = ATopDownTemplateGameCharacter::StaticClass();
}