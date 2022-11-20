// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/NPCAIControler.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy/AINPC.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enemy/BB_Keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

ANPCAIControler::ANPCAIControler(FObjectInitializer const& objectInitializer)
{
	static  ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/Asset/Enemy/IA/NPCAI.NPCAI'"));
	if (obj.Succeeded())
	{
		behaviorTree = obj.Object;
	}
	behaviorTreeComponent = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	setupPersceptionSys();
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

void ANPCAIControler::TagetDetected(AActor* actor, FAIStimulus const stimulus)
{
	getBlackboard()->SetValueAsBool(bb_keys::canSeePlayer, true);
}

void ANPCAIControler::setupPersceptionSys()
{
	//Create & Init sight config
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	sightConfig->SightRadius = 350.f;
	sightConfig->LoseSightRadius = sightConfig->SightRadius + 20.f;
	sightConfig->PeripheralVisionAngleDegrees = 90.f;
	sightConfig->SetMaxAge(5.f);
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 900.f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//Add sight config component to perception component
	GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIControler::TagetDetected);
	GetPerceptionComponent()->ConfigureSense(*sightConfig);

}


