// Copyright Epic Games, Inc. All Rights Reserved.


#include "GladiatorGameModeBase.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AGladiatorGameModeBase::AGladiatorGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	numberOfEnemiesAlive = 0;
	delayOfAttack = 1;

}

void AGladiatorGameModeBase::BeginPlay()
{
	UGameplayStatics::SpawnSound2D(this, backgroundSound);
	for (TActorIterator<AAINPC> actor(GetWorld()); actor; ++actor)
	{
		numberOfEnemiesAlive++;
	}

}

void AGladiatorGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!enemyIsAttacking && ChasingEnemies.Num() > 0)
	{

		enemyIsAttacking = true;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				if (ChasingEnemies.Num() > 0)
					ChasingEnemies[FMath::RandRange(0, ChasingEnemies.Num() - 1)]->willAttack = true;
			}, delayOfAttack, false);

	}

	if (numberOfEnemiesAlive <= 0)
	{
		enemyIsDead = true;
		FTimerHandle MemberTimerHandle2;
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle2, [&]()
			{
				DeadEnemy();
			}, 3, false);

	}
}

void AGladiatorGameModeBase::DeadEnemy()
{
	if (enemyIsDead)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		UGameplayStatics::OpenLevel(GetWorld(), "GGWinMenu");
	}
}
