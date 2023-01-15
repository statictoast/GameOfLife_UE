
#pragma once

#include "CoreMinimal.h"

/*
* LongLongCoordinate
* --------------------
* A 2D coordtinate in the space of [INT64_MIN, INT64_MAX]
*/
struct LongLongCoordinate
{
    LongLongCoordinate( int64 XCoord, int64 YCoord )
        : X(XCoord)
        , Y(YCoord)
    {
    }

    bool operator==(const LongLongCoordinate& Other)
    {
        return X == Other.X && Y == Other.Y;
    }

    bool operator==(const LongLongCoordinate& Other) const
    {
        return X == Other.X && Y == Other.Y;
    }

    int64 X = 0;
    int64 Y = 0;
};

// Taken from Vector2D version of GetTypeHash
inline uint32 GetTypeHash( const LongLongCoordinate& A )
{
    return FCrc::MemCrc_DEPRECATED( &A, sizeof( LongLongCoordinate ) );
}

/*
* GameOfLifeTestCase
* --------------------
* Helper class to define a starting state for the Game of Life to test the algorithm
*/

UENUM(BlueprintType)
enum class GOLTestCaseType : uint8
{
    Random,
    Block,
    BeeHive,
    Boat,
    Blinker,
    Beacon,
    Glider,
    ExtremeCoords
};

class GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) = 0;
};

class GameOfLifeTestRandom : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestBlock : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestBeeHive : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestBoat : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestBlinker : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestBeacon : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestGlider : public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

class GameOfLifeTestExtremeCoords: public GameOfLifeTestCase
{
public:
    virtual void LoadTest( TSet<LongLongCoordinate>& AliveNodes ) override;
};

