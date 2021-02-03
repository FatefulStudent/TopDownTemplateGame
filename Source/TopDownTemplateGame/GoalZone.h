#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalZone.generated.h"

class ASoccerBall;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOverlappedWithTheBall);

UCLASS()
class TOPDOWNTEMPLATEGAME_API AGoalZone : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category=Collision)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* ParticleSystem;
	
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	bool bTickOverlap = false;
	
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	bool bNotifyActorOverlap = false;

	UPROPERTY(EditDefaultsOnly, Category=Effects)
	bool bComponentDelegateOverlap = false;
	
public:
	AGoalZone();

protected:
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override; 

	UFUNCTION(BlueprintNativeEvent)
	void OnBallOverlapped(ASoccerBall* SoccerBall);

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

	UPROPERTY()
	TArray<ASoccerBall*> CachedOverlappedBalls;
};
