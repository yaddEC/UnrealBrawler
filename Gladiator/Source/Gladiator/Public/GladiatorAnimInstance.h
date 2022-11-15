// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerGladiator.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GladiatorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable,hideCategories=AnimInstance, BlueprintType)
class GLADIATOR_API UGladiatorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UGladiatorAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool Guard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		class UAnimInstance* UE_AnimInstance;




	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
