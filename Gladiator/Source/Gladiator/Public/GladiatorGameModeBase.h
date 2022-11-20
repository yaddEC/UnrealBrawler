// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/AINPC.h"
#include "GladiatorGameModeBase.generated.h"
#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}

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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TArray<AAINPC*> ChasingEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		bool enemyIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		int numberOfEnemiesAlive;
};
