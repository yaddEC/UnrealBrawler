// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Enemy/BB_Keys.h"

UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get player & NPC
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());

	//Get player location
	FVector const playerLocation = player->GetActorLocation();
	if(searchRandom)
	{
		FNavLocation loc;

		//Get nav System & Generate Random location near player
		UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
		if(navSys->GetRandomPointInNavigableRadius(playerLocation, seachRadius, loc, nullptr))
		{
			control->getBlackboard()->SetValueAsVector(bb_keys::targetLocation, loc.Location);
		}
	}
	else
	{
		control->getBlackboard()->SetValueAsVector(bb_keys::targetLocation, playerLocation);
	}

	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}
