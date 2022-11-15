// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UAnimInstanceEnemy : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UAnimInstanceEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
	float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	class UAnimInstance* UE_AnimInstance;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
