#include "Defender.h"


#include "TopDownTemplateGameCharacter.h"
#include "TopDownTemplateGameGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/TargetPoint.h"
#include "Perception/PawnSensingComponent.h"

ADefender::ADefender()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

void ADefender::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnHearNoise.AddDynamic(this, &ADefender::NoiseHeard);
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ADefender::PawnSeen);
}

void ADefender::BeginPlay()
{
	Super::BeginPlay();
	
	TryStartingPatrol();
}

void ADefender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == EDefenderState::Patrolling)
	{
		UpdateTargetPointIfNeeded();
	}
	if (State == EDefenderState::Chasing)
	{
		CheckIfHitCharacter();
	}
}

void ADefender::StartPatrolling()
{
	if (CurrentTargetPoint)
	{
		State = EDefenderState::Patrolling;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(),
		                                                CurrentTargetPoint->GetActorLocation());
	}
}

void ADefender::UpdateCurrentPatrolPoint()
{
	CurrentTargetPointIndex = FMath::Max(0, CurrentTargetPointIndex + 1);

	if (CurrentTargetPointIndex >= PatrollingPoints.Num())
	{
		CurrentTargetPointIndex = 0;
	}

	CurrentTargetPoint = PatrollingPoints[CurrentTargetPointIndex];
}

void ADefender::TryStartingPatrol()
{
	if (PatrollingPoints.Num() > 0)
	{
		if (!CurrentTargetPoint)
			UpdateCurrentPatrolPoint();
		
		StartPatrolling();
	}
}

void ADefender::UpdateTargetPointIfNeeded()
{
	const bool bGoalIsReached = GetHorizontalDistanceTo(CurrentTargetPoint) < AcceptanceRadius;
	if (bGoalIsReached)
	{
		UpdateCurrentPatrolPoint();
		StartPatrolling();
	}
}

void ADefender::CheckIfHitCharacter()
{
	if (ChasedPawn)
	{
		const bool bGotTooCloseToPawn = GetHorizontalDistanceTo(ChasedPawn) < AcceptanceRadius;
		if (bGotTooCloseToPawn)
		{
			if (auto GameMode = Cast<ATopDownTemplateGameGameMode>(GetWorld()->GetAuthGameMode()))
			{
				GameMode->OnCharacterHitByDefender();
			}
		}
		
	}
	
}

void ADefender::NoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (State == EDefenderState::Chasing)
		return;
	
	if (State == EDefenderState::Patrolling)
	{
		GetController()->StopMovement();
	}
	State = EDefenderState::Suspicious;
	RotateTowardsLocation(Location);
	
	GetWorldTimerManager().SetTimer(ReturnToPatrol_TimerHandle,
		this, &ADefender::StartPatrolling, 3.0f);
}

void ADefender::PawnSeen(APawn* SeenPawn)
{
	if (SeenPawn->IsA<ATopDownTemplateGameCharacter>())
	{
		State = EDefenderState::Chasing;
		ChasedPawn = SeenPawn; 
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), SeenPawn);
	}		
}

void ADefender::RotateTowardsLocation(const FVector& Location)
{
	const FVector NewDirection = Location - GetActorLocation();
	const FRotator NewActorRotation = NewDirection.ToOrientationRotator();
	SetActorRotation(NewActorRotation);
}

