#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoccerBall.generated.h"

UCLASS()
class TOPDOWNTEMPLATEGAME_API ASoccerBall : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Visual)
	UStaticMeshComponent* StaticMeshComponent;
	
public:
	ASoccerBall();
};
