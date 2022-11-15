// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AnimInstanceEnemy.h"

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
	}
}
