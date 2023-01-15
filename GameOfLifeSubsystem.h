
#pragma once

#include "CoreMinimal.h"
#include "GameOfLifeUtils.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameOfLifeSubsystem.generated.h"

/**
 * UGameOfLifeSubsystem 
 * 
 * WorldSubsystem for an implementation of Game of Life
 * 
 * Algorithm Explanation
 * ---------------------
 * 
 * System keeps track of the list of all Alive Nodes only.
 * Since a Dead Node can only become an Alive Node when adjacent to an Alive Node,
 * we only need to update Dead Nodes that are adjacent (neighbors) to Alive Nodes during that time step.
 * This will cull from calculations any node coordinates that are completely isolated by Dead Nodes.
 * Since the function for checking a node is recursive, we mark already calculated nodes in VisitedNodes 
 * so that if we see the same node more than once we don't waste time recalculating the Alive state again.
 * 
 * Algorithm History
 * ------------------
 * 
 * Originally this started out as a basic, array-based grid of bools to represent every coord state of a small
 * sized grid. This was used to help understand the algorithm and principles behind what the system is trying to accomplish
 * After getting a basic understanding of Game of Life, doing a bunch of research online, as well as discussing
 * solutions with friends, the next step was to try and implement a already known good solution, Hashlife.
 * While promising, it took a bit too long to realize that the purpose of Hashlife does not directly solve the given issue
 * since the purpose of Hashlife is to find states very far in the future. This lead to the approach being abbandoned.
 * Going back through the notes, the next best solution was to try and cull as most of the coordinates in the grid as possible
 * so the algorithm only calculates the minimum amount of coordinates per time step as possible.
 * Since a dead node can only become alive if it is adjacent to an alive node, we only need to keep track of alive nodes
 * and check its direct neighbors, alive or dead, along with updating the current alive node to determine the full grid state.
 * 
 * Future Improvements
 * --------------------
 * 
 * The current iteration does very well when multiple alive nodes are scattered throughout the grid, but
 * it has similar issues to the base algorithm where it will struggle in both memory and calculation speed
 * when there are many many alive nodes (10,000+). There are several ideas that could be used to improve this
 * current method:
 * 1. Instead of holding all alive nodes in a single large Set, a quadtree could be used to partition the nodes
 * into subsets based on with portion of the grid they belong in.
 * 2. Combined with using the quadtree, this would allow for multithreading to be used to calculate each sub-partition
 * in the quadtree since each node's next state can be calculated independently of every other one.
 * 3. Within the quadtree structure, there could even be memory savings by utilizing memoization of data.
 * By hashing a 4x4 or 2x2 grid, we can use the same data representation in multiple sub-partitions in the quadtree.
 * 
 * References
 * -----------
 * 
 * https://codereview.stackexchange.com/questions/47167/conways-game-of-life-in-c
 * https://www.geeksforgeeks.org/program-for-conways-game-of-life/
 * https://github.com/MarioTalevski/game-of-life/blob/master/GameOfLife.cpp
 * https://johnhw.github.io/hashlife/index.md.html
 * 
 */
UCLASS()
class GAMEOFLIFE_API UGameOfLifeSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize( FSubsystemCollectionBase& Collection ) override;
	virtual void Deinitialize() override;
	virtual void Tick( float DeltaTime ) override;
	virtual TStatId GetStatId() const override;

public:

	void ResetSimulation();

	void StartWithTestCase( GameOfLifeTestCase* Test );

	void SetUpdatePeriod( float PeriodS ) { UpdatePeriodS = PeriodS; }

	const TSet<LongLongCoordinate>& GetCurrentAliveNodes() { return *CurrentAliveNodesPtr; }

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSimulatingLife() { return bIsSimulating; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetNumUpdatesCurrentTimestep() { return NumUpdatesCurrentTimestep; }

protected:

	const int64 MinGridSizeX = TNumericLimits<int64>::Min();
	const int64 MaxGridSizeX = TNumericLimits<int64>::Max();
	const int64 MinGridSizeY = TNumericLimits<int64>::Min();
	const int64 MaxGridSizeY = TNumericLimits<int64>::Max();

	void UpdateGridLifeCycle();
	void CalculateLifeAtCoord( const LongLongCoordinate& CoordsToCheck );

protected:

	float UpdatePeriodS = 0.f;
	float CurrentTimeElapsed = 0.f;

	int32 NumUpdatesCurrentTimestep = 0;

	bool bIsSimulating = false;

	TSet<LongLongCoordinate> FirstAliveNodes;
	TSet<LongLongCoordinate> SecondAliveNodes;

	TSet<LongLongCoordinate>* CurrentAliveNodesPtr = nullptr;
	TSet<LongLongCoordinate>* PreviousAliveNodesPtr = nullptr;

	TSet<LongLongCoordinate> VisitedNodes;
};
