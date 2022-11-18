// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AnimInstanceEnemy.h"
#include "Enemy/AINPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Enemy/EnemyCanAttack.h"
#include "Enemy/BB_Keys.h"

UAnimInstanceEnemy::UAnimInstanceEnemy()
{
	Speed = 0;
	Direction = 0;
}

void UAnimInstanceEnemy::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		Speed = OwningActor->GetVelocity().Size();
		Direction = UE_AnimInstance->CalculateDirection(OwningActor->GetVelocity(), OwningActor->GetActorRotation());
		ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AAINPC* npc = Cast<AAINPC>(OwningActor);
		if(npc)
		{
			Attack = npc->isEnemyAttacking;
		}
	}
}
