// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
