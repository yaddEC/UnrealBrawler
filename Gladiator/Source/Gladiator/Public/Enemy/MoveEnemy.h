// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MoveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMoveEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UMoveEnemy(FObjectInitializer const& objectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
