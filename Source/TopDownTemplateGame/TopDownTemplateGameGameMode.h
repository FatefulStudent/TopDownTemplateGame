// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopDownTemplateGameGameMode.generated.h"

UCLASS(minimalapi)
class ATopDownTemplateGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATopDownTemplateGameGameMode();
	void OnGoalScored();
	void OnCharacterHitByDefender();
private:
	void RestartLevel();
};



