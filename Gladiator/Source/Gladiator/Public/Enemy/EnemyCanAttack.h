// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EnemyCanAttack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UEnemyCanAttack : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UEnemyCanAttack();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float AttackRange = 25.f;
};
