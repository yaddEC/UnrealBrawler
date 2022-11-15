// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChasePlayer.h"

#include "AVEncoder/Public/CodecPacket.h"
#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemy/BB_Keys.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIControler* const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	FVector const PlayerLocation = control->getBlackboard()->GetValueAsVector(bb_keys::targetLocation);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, PlayerLocation);
	
	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}


