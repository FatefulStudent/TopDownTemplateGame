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
	// ResetLevel();
	// RestartPlayer(GetWorld()->GetFirstPlayerController());

	FString CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);
	FName CurrentLevelFName {*CurrentLevelName};
	UGameplayStatics::OpenLevel(this, CurrentLevelFName);
}
