// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Enemy/BB_Keys.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}

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

	AAINPC* npc2 = Cast<AAINPC>(control->GetPawn());


	UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSys->GetRandomPointInNavigableRadius(origin, radius, loc, nullptr))
	{
		control->getBlackboard()->SetValueAsVector(bb_keys::targetLocation, loc.Location);
		if (npc2)
		{

			if (!npc2->MovOry)
			{

				if (UCharacterMovementComponent* MC = npc2->GetCharacterMovement())
				{
					MC->bOrientRotationToMovement = true;
					npc2->MovOry = true;
				}
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
