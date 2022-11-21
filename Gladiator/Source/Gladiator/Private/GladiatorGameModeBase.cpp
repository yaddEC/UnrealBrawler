// Copyright Epic Games, Inc. All Rights Reserved.


#include "GladiatorGameModeBase.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AGladiatorGameModeBase::AGladiatorGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	numberOfEnemiesAlive = 0;

}

void AGladiatorGameModeBase::BeginPlay()
{
	UGameplayStatics::SpawnSound2D(this, backgroundSound);
	for (TActorIterator<AAINPC> actor(GetWorld()); actor; ++actor)
	{
		/*AAINPC* enemy = Cast<AAINPC>(*actor);
		enemies.Add(enemy);*/
		numberOfEnemiesAlive++;
	}

}

void AGladiatorGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Debug("ChasingEnemies = %d",ChasingEnemies.Num());
	if (!enemyIsAttacking && ChasingEnemies.Num() != 0)
	{

		enemyIsAttacking = true;
		FTimerHandle TimerHandle;
		//int numChasingEnemies = ChasingEnemies.Num();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				//Debug("range = %d", range);
				if (ChasingEnemies.Num() != 0)
					ChasingEnemies[FMath::RandRange(0, ChasingEnemies.Num() - 1)]->willAttack = true;
			}, 1, false);

	}
}
