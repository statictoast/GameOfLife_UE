// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifeUtils.h"

void GameOfLifeTestRandom::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    for( int64 i = -100; i < 100; i++ )
    {
        for( int64 j = -100; j < 100; j++ )
        {
            if( FMath::RandRange( 1, 100 ) > 90 ) // 10% of all grid coords
            {
                AliveNodes.Add( LongLongCoordinate( i, j ) );
            }
        }
    }
}

void GameOfLifeTestBlock::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 0, 1 ) );
    AliveNodes.Add( LongLongCoordinate( 0, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 1 ) );
}

void GameOfLifeTestBeeHive::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 0, 1 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 1 ) );
}

void GameOfLifeTestBoat::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 0, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 1 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 1 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 2 ) );
}

void GameOfLifeTestBlinker::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 2, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 1 ) );
}

void GameOfLifeTestBeacon::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 1, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 4, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 4, 1 ) );
}

void GameOfLifeTestGlider::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    AliveNodes.Add( LongLongCoordinate( 2, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 2 ) );
    AliveNodes.Add( LongLongCoordinate( 3, 3 ) );
    AliveNodes.Add( LongLongCoordinate( 2, 4 ) );
    AliveNodes.Add( LongLongCoordinate( 4, 3 ) );
}

void GameOfLifeTestExtremeCoords::LoadTest( TSet<LongLongCoordinate>& AliveNodes )
{
    const int64 MinGridSizeX = TNumericLimits<int64>::Min();
    const int64 MaxGridSizeX = TNumericLimits<int64>::Max();
    const int64 MinGridSizeY = TNumericLimits<int64>::Min();
    const int64 MaxGridSizeY = TNumericLimits<int64>::Max();

    AliveNodes.Add( LongLongCoordinate( 0, 1 ) );
    AliveNodes.Add( LongLongCoordinate( 0, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 0 ) );
    AliveNodes.Add( LongLongCoordinate( 1, 1 ) );

    AliveNodes.Add( LongLongCoordinate( 7, 8 ) );
    AliveNodes.Add( LongLongCoordinate( 7, 7 ) );
    AliveNodes.Add( LongLongCoordinate( 8, 7 ) );
    AliveNodes.Add( LongLongCoordinate( 8, 8 ) );

    AliveNodes.Add( LongLongCoordinate( -7, -8 ) );
    AliveNodes.Add( LongLongCoordinate( -7, -7 ) );
    AliveNodes.Add( LongLongCoordinate( -8, -7 ) );
    AliveNodes.Add( LongLongCoordinate( -8, -8 ) );

    AliveNodes.Add( LongLongCoordinate( -200000000000000, -200000000000000 ) );
    AliveNodes.Add( LongLongCoordinate( -200000000000001, -200000000000001 ) );
    AliveNodes.Add( LongLongCoordinate( 200000000000000, 200000000000000 ) );
    AliveNodes.Add( LongLongCoordinate( 200000000000001, 200000000000001 ) );

    AliveNodes.Add( LongLongCoordinate( MinGridSizeX + 10, MinGridSizeY + 11 ) );
    AliveNodes.Add( LongLongCoordinate( MinGridSizeX + 10, MinGridSizeY + 12 ) );
    AliveNodes.Add( LongLongCoordinate( MinGridSizeX + 10, MinGridSizeY + 13 ) );

    AliveNodes.Add( LongLongCoordinate( MaxGridSizeX - 1, MinGridSizeY + 10 ) );
    AliveNodes.Add( LongLongCoordinate( MaxGridSizeX, MinGridSizeY + 10 ) );
    AliveNodes.Add( LongLongCoordinate( MaxGridSizeX - 1, MinGridSizeY + 9 ) );
    AliveNodes.Add( LongLongCoordinate( MaxGridSizeX, MinGridSizeY + 9 ) );
}