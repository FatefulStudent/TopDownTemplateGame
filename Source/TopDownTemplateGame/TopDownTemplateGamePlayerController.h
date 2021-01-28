// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownTemplateGamePlayerController.generated.h"

UCLASS()
class ATopDownTemplateGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownTemplateGamePlayerController();

protected:
	UPROPERTY(EditDefaultsOnly)
	float MinDistanceToMoveTo = 120.0f;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	bool bMoveToMouseCursor = false;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};


