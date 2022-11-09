// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "RandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GLADIATOR_API URandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	URandomLocation(FObjectInitializer const& objectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float radius = 1500.f;
	
};
