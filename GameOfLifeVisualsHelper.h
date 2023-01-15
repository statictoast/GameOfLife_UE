
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOfLifeVisualsHelper.generated.h"

class GameOfLifeTestCase;

UCLASS()
class GAMEOFLIFE_API AGameOfLifeVisualsHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOfLifeVisualsHelper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* GetOrCreateAliveNode();

	void DeactivateAliveNode( AActor* AliveNode );

	void ClearAllAliveNodes();

public:	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

public:

	UFUNCTION(BlueprintCallable)
	void StartGameOfLife( GOLTestCaseType TestCaseType );

	UFUNCTION(BlueprintCallable)
	void StopGameOfLife();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BaseAliveNodeActorClass;

	UPROPERTY()
	TArray<AActor*> AliveNodeActors;

	// Tracks number of nodes used in current time step. 
	// Allows system to recycle Actors without having to 
	// move from a deactive to active list and vice versa
	int32 ActiveNodesCount = 0;

	const int16 MaxGridPosition = TNumericLimits<int16>::Max();

	TMap<GOLTestCaseType, GameOfLifeTestCase*> TestCasesMap;
};
