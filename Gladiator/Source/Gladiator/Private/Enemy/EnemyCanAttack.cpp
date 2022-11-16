// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCanAttack.h"
#include "Enemy/NPCAIControler.h"
#include "Enemy/AINPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BB_Keys.h"

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}

UEnemyCanAttack::UEnemyCanAttack()
{
	NodeName = TEXT("Enemy Can Attack");
}

void UEnemyCanAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get NPC
	ANPCAIControler* const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	AAINPC* const npc = Cast<AAINPC>(control->GetPawn());

	//Get player character
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	//BlackBoard bool
	npc->isAttacking = npc->GetDistanceTo(player) <= AttackRange;
	control->getBlackboard()->SetValueAsBool(bb_keys::enemyAttack, npc->isAttacking);
	Debug("P = %f", npc->GetDistanceTo(player));
	Debug("E = %f", AttackRange);
}
