// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifeSubsystem.h"

void UGameOfLifeSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
    Super::Initialize( Collection );

    ResetSimulation();
}

void UGameOfLifeSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

TStatId UGameOfLifeSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT( UGameOfLifeSubsystem, STATGROUP_Tickables );
}

void UGameOfLifeSubsystem::ResetSimulation()
{
    CurrentAliveNodesPtr = &FirstAliveNodes;
    PreviousAliveNodesPtr = &SecondAliveNodes;

    FirstAliveNodes.Empty();
    SecondAliveNodes.Empty();

    CurrentTimeElapsed = 0.f;

    NumUpdatesCurrentTimestep = 0;

    bIsSimulating = false;
}

void UGameOfLifeSubsystem::StartWithTestCase( GameOfLifeTestCase* Test )
{
    ResetSimulation();
    Test->LoadTest( FirstAliveNodes );
    bIsSimulating = true;
}

void UGameOfLifeSubsystem::Tick( float DeltaTime )
{
    if( !bIsSimulating )
    {
        return;
    }

    CurrentTimeElapsed += DeltaTime;
    if( CurrentTimeElapsed >= UpdatePeriodS )
    {
        CurrentTimeElapsed = FMath::Max( CurrentTimeElapsed - UpdatePeriodS, 0.f );
        NumUpdatesCurrentTimestep = 0;
        UpdateGridLifeCycle();
    }
}

void UGameOfLifeSubsystem::UpdateGridLifeCycle()
{
    // swap buffers so previous is current (old) and current is previous (but we will update that in a sec)
    // empty the Current Set so we populate it with the correct Alive nodes for this timestep
    TSet<LongLongCoordinate>* SwapHelper = CurrentAliveNodesPtr;
    CurrentAliveNodesPtr = PreviousAliveNodesPtr;
    PreviousAliveNodesPtr = SwapHelper;
    CurrentAliveNodesPtr->Empty();

    VisitedNodes.Empty();
    // loop through alive nodes and calculate the life state at that position as well as neighbors
    for( const LongLongCoordinate& PrevAliveCoord : ( *PreviousAliveNodesPtr ) )
    {
        CalculateLifeAtCoord( PrevAliveCoord );
    }
}

void UGameOfLifeSubsystem::CalculateLifeAtCoord( const LongLongCoordinate& CoordsToCheck )
{
    // only update Nodes we have seen for the first time
    if( VisitedNodes.Contains( CoordsToCheck ) )
    {
        return;
    }

    NumUpdatesCurrentTimestep++;

    VisitedNodes.Add( CoordsToCheck );
    bool bIsAlreadyAlive = ( *PreviousAliveNodesPtr ).Contains( CoordsToCheck );
    uint32 NumAliveNeighbors = 0;
    for( int YDiff = -1; YDiff < 2; YDiff++ )
    {
        for( int XDiff = -1; XDiff < 2; XDiff++ )
        {
            if( !( YDiff == 0 && XDiff == 0 ) )
            {
                // check to make sure next value would not go off the grid
                if( ( CoordsToCheck.X == MaxGridSizeX && XDiff == 1 )
                    || (CoordsToCheck.X == MinGridSizeX && XDiff == -1)
                    || (CoordsToCheck.Y == MaxGridSizeY && YDiff == 1)
                    || ( CoordsToCheck.Y == MinGridSizeY && YDiff == -1) )
                {
                    continue;
                }

                const int64 NextX = ( CoordsToCheck.X + XDiff );
                const int64 NextY = ( CoordsToCheck.Y + YDiff );
                LongLongCoordinate NeighborToCheck( NextX, NextY );

                if( ( *PreviousAliveNodesPtr ).Contains( NeighborToCheck ) )
                {
                    NumAliveNeighbors++;
                }

                if( bIsAlreadyAlive )
                {
                    // since an alive node was being checked, NeighborToCheck could also need to updated so let's update it
                    CalculateLifeAtCoord( NeighborToCheck );
                }
            }
        }
    }

    // Since we have removed all alive nodes from CurrentAliveNodesPtr, we only need to add nodes that should be alive at this timestep
    if( (( bIsAlreadyAlive && NumAliveNeighbors  == 2) || NumAliveNeighbors == 3 ) )
    {
        ( *CurrentAliveNodesPtr ).Add( CoordsToCheck );
    }
}