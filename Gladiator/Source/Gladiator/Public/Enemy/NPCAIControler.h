// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCAIControler.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API ANPCAIControler : public AAIController
{
	GENERATED_BODY()

public:
	ANPCAIControler(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* getBlackboard() const;
};
