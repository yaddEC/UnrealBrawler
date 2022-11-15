// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCanAttack.h"
#include "Enemy/NPCAIControler.h"
#include "Enemy/AINPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BB_Keys.h"

UEnemyCanAttack::UEnemyCanAttack()
{
	NodeName = TEXT("Enemy Can Attack");
}

void UEnemyCanAttack::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	//Get NPC
	ANPCAIControler* const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	AAINPC* const npc = Cast<AAINPC>(control->GetPawn());

	//Get player character
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//BlackBoard bool
	control->getBlackboard()->SetValueAsBool(bb_keys::enemyAttack, npc->GetDistanceTo(player) <= AttackRange);
	
}
