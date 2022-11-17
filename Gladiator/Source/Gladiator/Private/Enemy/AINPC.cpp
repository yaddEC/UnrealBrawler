// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AINPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "PlayerGladiator.h"


// Sets default values
AAINPC::AAINPC()
{

	

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	gotHit = false;
	Health = 3;
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	setupStimulus();
}

void AAINPC::setupStimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void AAINPC::BeginPlay()
{
	Super::BeginPlay();
			enemy = GetMesh();
		if (enemy)
		{
			Material = enemy->GetMaterial(0);
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
			enemy->SetMaterial(0, DynamicMaterial);
		}
}

// Called every frame
void AAINPC::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (gotHit && hitColor <= 0)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), hitColor);
		hitColor =1;
		Debug("mat = %f", hitColor);
	}
	else if (hitColor > 0)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), hitColor);
		hitColor -= 0.01f;
		if (hitColor < 0.01f && gotHit)
			hitColor = 0.01f;
		Debug("mat = %f", hitColor);
	}

	
	if (Health <= 0)
	{
		Destroy();
	}


}

// Called to bind functionality to input
void AAINPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAINPC::ApplyDamage(float Damage)
{
	if (!gotHit)
	{

		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
		enemy->SetMaterial(0, DynamicMaterial);
		gotHit = true;
		Health -= Damage;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				gotHit = false;
			}, 1, false);
	}
}
