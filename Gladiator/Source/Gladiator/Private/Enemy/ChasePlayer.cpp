// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChasePlayer.h"

#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemy/BB_Keys.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}



UChasePlayer::UChasePlayer(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIControler* const control = Cast<ANPCAIControler>(OwnerComp.GetAIOwner());
	AAINPC* npc = Cast<AAINPC>(control->GetPawn());
	FVector const playerLocation = control->getBlackboard()->GetValueAsVector(bb_keys::targetLocation);
	FVector const npcLocation = control->GetPawn()->GetActorLocation();
	FVector playerToNpc = npcLocation - playerLocation;
	float dist = playerToNpc.Size();
	playerToNpc.Normalize();


	//Get nav System & Generate Random location near player
	if (dist > 200)
	{
		Debug("Enemy dist = %f", dist);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, playerLocation + playerToNpc * 300);
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, npcLocation + playerToNpc * 400);

		if (npc)
		{
			if (npc->MovOry)
			{
				if (UCharacterMovementComponent* MC = npc->GetCharacterMovement())
				{
					MC->bOrientRotationToMovement = false;
					npc->MovOry = false;
				}
			}

		}
	}

	if (!npc->isAttacking)
	{
		npc->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(-playerToNpc, FVector::UpVector));
	}

	//control->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(playerToNpc , FVector::UpVector));

	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}


