// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifeVisualsHelper.h"
#include "GameOfLifeSubsystem.h"
#include "GameOfLifeUtils.h"

// Sets default values
AGameOfLifeVisualsHelper::AGameOfLifeVisualsHelper()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameOfLifeVisualsHelper::BeginPlay()
{
	Super::BeginPlay();
	if( UGameOfLifeSubsystem* GameOfLife = GetWorld()->GetSubsystem<UGameOfLifeSubsystem>() )
	{
		GameOfLife->SetUpdatePeriod( 0.5f );
	}

	TestCasesMap.Add( GOLTestCaseType::Random, new GameOfLifeTestRandom() );
	TestCasesMap.Add( GOLTestCaseType::Block, new GameOfLifeTestBlock() );
	TestCasesMap.Add( GOLTestCaseType::BeeHive, new GameOfLifeTestBeeHive() );
	TestCasesMap.Add( GOLTestCaseType::Boat, new GameOfLifeTestBoat() );
	TestCasesMap.Add( GOLTestCaseType::Blinker, new GameOfLifeTestBlinker() );
	TestCasesMap.Add( GOLTestCaseType::Beacon, new GameOfLifeTestBeacon() );
	TestCasesMap.Add( GOLTestCaseType::Glider, new GameOfLifeTestGlider() );
	TestCasesMap.Add( GOLTestCaseType::ExtremeCoords, new GameOfLifeTestExtremeCoords() );
}

// Called every frame
void AGameOfLifeVisualsHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClearAllAliveNodes();

	UGameOfLifeSubsystem* GameOfLife = GetWorld()->GetSubsystem<UGameOfLifeSubsystem>();
	if( !GameOfLife )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Game Of Life World Subsystem does not exist." ) );
		return;
	}

	const TSet<LongLongCoordinate>& CurrentNodes = GameOfLife->GetCurrentAliveNodes();

	int32 NumNodesInLife = CurrentNodes.Num();
	for( const LongLongCoordinate& AliveNodeCoord : CurrentNodes )
	{
		if( FMath::Abs( AliveNodeCoord.X ) > MaxGridPosition
			|| FMath::Abs( AliveNodeCoord.Y ) > MaxGridPosition )
		{
			// HACK: Unreal Physics does not like setting actors at very large values, 
			// so skip adding this node since it will be so far away from origin no one would see it anyways
			NumNodesInLife--;
			continue;
		}

		AActor* NodeActor = GetOrCreateAliveNode();
		
		NodeActor->SetActorLocation( FVector( AliveNodeCoord.X * 100.f, AliveNodeCoord.Y * 100.f, 0.f ) );
	}

	// if we have less Alive nodes than total created AliveNodesActors, we need to "hide" the inactive ones
	for( int32 i = NumNodesInLife; i < AliveNodeActors.Num(); ++i )
	{
		DeactivateAliveNode( AliveNodeActors[i] );
	}
}

AActor* AGameOfLifeVisualsHelper::GetOrCreateAliveNode()
{
	AActor* ReturnActor = nullptr;
	if( ActiveNodesCount < AliveNodeActors.Num() )
	{
		ReturnActor = AliveNodeActors[ActiveNodesCount++];
	}
	else
	{
		ReturnActor = GetWorld()->SpawnActor<AActor>( BaseAliveNodeActorClass );
		ReturnActor->SetActorEnableCollision( false );
		AliveNodeActors.Push( ReturnActor );
		ActiveNodesCount++;
	}

	if( ReturnActor )
	{
		ReturnActor->SetActorHiddenInGame( false );
	}
	return ReturnActor;
}

void AGameOfLifeVisualsHelper::DeactivateAliveNode( AActor* AliveNode )
{
	AliveNode->SetActorHiddenInGame( true );
}

void AGameOfLifeVisualsHelper::ClearAllAliveNodes()
{
	ActiveNodesCount = 0;
}

void AGameOfLifeVisualsHelper::StartGameOfLife( GOLTestCaseType TestCaseType )
{
	GameOfLifeTestCase* TestCase = TestCasesMap[TestCaseType];
	if( UGameOfLifeSubsystem* GameOfLife = GetWorld()->GetSubsystem<UGameOfLifeSubsystem>() )
	{
		GameOfLife->StartWithTestCase( TestCase );
	}
}

void AGameOfLifeVisualsHelper::StopGameOfLife()
{
	if( UGameOfLifeSubsystem* GameOfLife = GetWorld()->GetSubsystem<UGameOfLifeSubsystem>() )
	{
		GameOfLife->ResetSimulation();
	}
}