// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownTemplateGameGameMode.h"
#include "TopDownTemplateGamePlayerController.h"
#include "TopDownTemplateGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATopDownTemplateGameGameMode::ATopDownTemplateGameGameMode()
{
	PlayerControllerClass = ATopDownTemplateGamePlayerController::StaticClass();
	DefaultPawnClass = ATopDownTemplateGameCharacter::StaticClass();
}

void ATopDownTemplateGameGameMode::OnGoalScored()
{
	RestartLevel();
}

void ATopDownTemplateGameGameMode::OnCharacterHitByDefender()
{
	RestartLevel();
}

void ATopDownTemplateGameGameMode::RestartLevel()
{
	// ResetLevel();
	// RestartPlayer(GetWorld()->GetFirstPlayerController());

	const FString CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);
	const FName CurrentLevelFName {*CurrentLevelName};
	UGameplayStatics::OpenLevel(this, CurrentLevelFName);
}
