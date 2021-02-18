#pragma once

#include "GameFramework/Character.h"

#include "Defender.generated.h"

class ATargetPoint;
class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EDefenderState : uint8
{
	Idle,
	Patrolling,
	Suspicious,
	Chasing,
};

UCLASS()
class TOPDOWNTEMPLATEGAME_API ADefender : public ACharacter
{
	GENERATED_BODY()

public:
	ADefender();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void StartPatrolling();
	void UpdateCurrentPatrolPoint();
	void TryStartingPatrol();
	void UpdateTargetPointIfNeeded();
	void CheckIfHitCharacter();

	UFUNCTION()	void NoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);
	UFUNCTION()	void PawnSeen(APawn* SeenPawn);

	void RotateTowardsLocation(const FVector& Location);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditInstanceOnly)
	TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 50.f;
	
	UPROPERTY() ATargetPoint* CurrentTargetPoint;
	UPROPERTY() APawn* ChasedPawn;
	int32 CurrentTargetPointIndex = INDEX_NONE;

	FTimerHandle ReturnToPatrol_TimerHandle;

	EDefenderState State = EDefenderState::Idle;
};
