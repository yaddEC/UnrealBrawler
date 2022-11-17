// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AINPC.h"
#include "ChasePlayer.generated.h"

/**
 *
 */
UCLASS()
class GLADIATOR_API UChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UChasePlayer(FObjectInitializer const& objectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float searchRadius = 150.f;

};
