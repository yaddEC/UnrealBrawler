// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Attack.h"

#include "AIController.h"
#include "Enemy/AINPC.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BB_Keys.h"

UAttack::UAttack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const control = OwnerComp.GetAIOwner();
	AAINPC* npc = Cast<AAINPC>(control->GetPawn());
	if(npc)
	{
		npc->isEnemyAttacking = true;
	}
	
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
