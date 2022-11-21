// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChasePlayer.h"

#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemy/BB_Keys.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/AINPC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	if (npc)
	{
		if (!npc->isChasing)
		{
			npc->isChasing = true;
			AGladiatorGameModeBase* GameMode = Cast<AGladiatorGameModeBase>(UGameplayStatics::GetGameMode(this));
			GameMode->ChasingEnemies.Add(npc);
		}
		if (npc->willAttack)
		{
			if (dist > 25)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, playerLocation + playerToNpc * 80);

			}
			
		}
		else
		{
			//Get nav System & Generate Random location near player
			if (dist > 350)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, playerLocation + playerToNpc * 350);
			}
			else if (dist < 300)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(control, npcLocation + playerToNpc * 400);



				control->getBlackboard()->SetValueAsBool(bb_keys::enemyIsDead, npc->isDead);

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
		if (!npc->isEnemyAttacking)
		{
			npc->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(-playerToNpc, FVector::UpVector));
		}



	}
	//Sucess
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}


