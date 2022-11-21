// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MoveEnemy.h"

#include "Enemy/NPCAIControler.h"
#include "Enemy/AINPC.h"
#include "Enemy/BB_Keys.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

UMoveEnemy::UMoveEnemy(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Move Enemy");
}

EBTNodeResult::Type UMoveEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ANPCAIControler* const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	AAINPC* npc = Cast<AAINPC>(control->GetPawn());
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const FVector PlayerLocation = player->GetActorLocation();
	const FVector AiLocation = control->GetPawn()->GetActorLocation();
	FVector AiToPlayer = PlayerLocation - AiLocation;
	AiToPlayer.Normalize();

	control->MoveToLocation(AiLocation + FVector::CrossProduct(AiToPlayer, FVector::UpVector) * 200);
	
	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
	
}
