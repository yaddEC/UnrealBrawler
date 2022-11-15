// Fill out your copyright notice in the Description page of Project Settings.


#include "GladiatorAnimInstance.h"

UGladiatorAnimInstance::UGladiatorAnimInstance()
{
	Speed = 0;
	Direction = 0;

}



void UGladiatorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr)
	{
		Speed = OwningActor->GetVelocity().Size();
		Direction = UE_AnimInstance->CalculateDirection(OwningActor->GetVelocity(), OwningActor->GetActorRotation());
		APlayerGladiator* OwningChar = Cast<APlayerGladiator>(OwningActor);
		if (OwningChar)
		{
			Guard = OwningChar->isBlocking;
			Attack = OwningChar->isAttacking;
		}

	}
}