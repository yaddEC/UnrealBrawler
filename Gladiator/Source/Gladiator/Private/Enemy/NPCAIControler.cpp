// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy/AINPC.h"

ANPCAIControler::ANPCAIControler(FObjectInitializer const& objectInitializer)
{
	static  ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/Asset/Enemy/IA/NPCAI.NPCAI'"));
	if(obj.Succeeded())
	{
		behaviorTree = obj.Object;
	}
	behaviorTreeComponent = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

}

void ANPCAIControler::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behaviorTree);
	behaviorTreeComponent->StartTree(*behaviorTree);
}

void ANPCAIControler::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*behaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* ANPCAIControler::getBlackboard() const
{
	return blackboard;
}


