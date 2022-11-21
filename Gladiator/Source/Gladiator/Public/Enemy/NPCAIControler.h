// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPCAIControler.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API ANPCAIControler : public AAIController
{
	GENERATED_BODY()
public:
	ANPCAIControler(FObjectInitializer const& objectInitializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const InPawn) override;
	void OnUnPossess() override;
	class UBlackboardComponent* getBlackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = "true"))
	class UBehaviorTree* behaviorTree;

	class UBlackboardComponent* blackboard;

	class UAISenseConfig_Sight* sightConfig;

	UFUNCTION()
	void TagetDetected(AActor* actor, FAIStimulus const stimulus);

	void setupPersceptionSys();
	
};
