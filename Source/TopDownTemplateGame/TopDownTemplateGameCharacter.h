// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownTemplateGameCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownTemplateGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownTemplateGameCharacter();

	// Called every frame.
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

protected:
	void MoveUp(float Value);
	void MoveRight(float Value);

	void BeginSprint();
	void EndSprint();

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UDecalComponent* CursorToWorld;
	
	/** A component that is responsible for noise making. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin=0))
	float WalkSpeed = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin=0))
	float SprintSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> NoiseCauserActor; 
	
};

