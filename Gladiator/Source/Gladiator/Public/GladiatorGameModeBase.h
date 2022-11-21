// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/AINPC.h"
#include "GladiatorGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class GLADIATOR_API AGladiatorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	AGladiatorGameModeBase();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void DeadEnemy();
public:
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* backgroundSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TArray<AAINPC*> ChasingEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		bool enemyIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		bool enemyIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		int numberOfEnemiesAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		float delayOfAttack;
};
