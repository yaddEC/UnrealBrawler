// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Enemy/AINPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Enemy/BB_Keys.h"

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}

UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get player & NPC
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	
	AAINPC* npc = Cast<AAINPC>(control->GetPawn());
	FVector const npcLocation = control->GetPawn()->GetActorLocation();

	//Get player location
	FVector const playerLocation = player->GetActorLocation();

	//BlackBoard Value as Vector 
	control->getBlackboard()->SetValueAsVector(bb_keys::targetLocation, playerLocation);

	//Raycast
	FHitResult HitResult;
	FCollisionQueryParams TraceParam; TraceParam.AddIgnoredActor(Cast<AActor>(control->GetPawn()));
	if (GetWorld()->LineTraceSingleByChannel(HitResult, npcLocation, playerLocation, ECC_GameTraceChannel1, TraceParam))
	{
		Debug("A");
		control->getBlackboard()->SetValueAsBool(bb_keys::enemySeeEnemy, true);
	}
	else
	{
		control->getBlackboard()->SetValueAsBool(bb_keys::enemySeeEnemy, false);
	}

	//Draw Raycast
	DrawDebugLine(GetWorld(), npcLocation, playerLocation, FColor::White, false, 1, 0, 1);

	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}
