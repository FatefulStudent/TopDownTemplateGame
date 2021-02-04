#include "GoalZone.h"
#include "SoccerBall.h"
#include "TopDownTemplateGameGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AGoalZone::AGoalZone()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetHiddenInGame(false);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCanEverAffectNavigation(false);
	RootComponent = BoxComponent;
}

void AGoalZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoalZone::OnOverlapBegin);
}

void AGoalZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bTickOverlap)
		return;

	TArray<FOverlapResult> CurrentOverlaps;
	BoxComponent->ComponentOverlapMulti(CurrentOverlaps,
		GetWorld(),
		BoxComponent->GetComponentLocation(),
		BoxComponent->GetComponentQuat(),
		BoxComponent->GetCollisionObjectType());

	TArray<ASoccerBall*> CurrentOverlappedBalls;
	
	for (const FOverlapResult& OverlapResult : CurrentOverlaps)
	{
		AActor* OtherActor = OverlapResult.GetActor();
		
		if (ASoccerBall* SoccerBall = Cast<ASoccerBall>(OtherActor))
		{
			if (!CachedOverlappedBalls.Contains(SoccerBall))
			{
				UE_LOG(LogTemp, Warning, TEXT("TickOverlap: overlapped with %s"), *SoccerBall->GetName())
				OnBallOverlapped(SoccerBall);
			}
			
			CurrentOverlappedBalls.Add(SoccerBall);
		}
	}

	CachedOverlappedBalls = CurrentOverlappedBalls;
}

void AGoalZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!bNotifyActorOverlap)
		return;
	
	if (ASoccerBall* SoccerBall = Cast<ASoccerBall>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("NotifyActorBeginOverlap: overlapped with %s"), *SoccerBall->GetName())
		OnBallOverlapped(SoccerBall);
	}
}

void AGoalZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bComponentDelegateOverlap)
		return;
	
	if (ASoccerBall* SoccerBall = Cast<ASoccerBall>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin: overlapped with %s"), *SoccerBall->GetName())
		OnBallOverlapped(SoccerBall);
	}
}

void AGoalZone::OnBallOverlapped_Implementation(ASoccerBall* SoccerBall)
{
	UGameplayStatics::SpawnEmitterAttached(ParticleSystem, SoccerBall->GetRootComponent());

	if (auto GameMode = GetWorld()->GetAuthGameMode<ATopDownTemplateGameGameMode>())
	{
		GameMode->OnGoalScored();
	}
}
