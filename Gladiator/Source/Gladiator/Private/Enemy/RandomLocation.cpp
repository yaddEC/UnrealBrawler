// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Enemy/BB_Keys.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URandomLocation::URandomLocation(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type URandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	auto const npc = control->GetPawn();

	FVector const origin = npc->GetActorLocation();
	FNavLocation loc;

	
	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSys->GetRandomPointInNavigableRadius(origin, radius, loc, nullptr))
	{
		control->getBlackboard()->SetValueAsVector(bb_keys::targetLocation, loc.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
