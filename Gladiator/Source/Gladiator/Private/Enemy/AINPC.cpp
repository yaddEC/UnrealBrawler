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
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/NPCAIControler.h"
#include "DrawDebugHelpers.h"
#include "PlayerGladiator.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GladiatorGameModeBase.h"
#include "Enemy/NPCAIControler.h"



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
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAINPC::Timer, 0.01f, true, 0.0f);
}

// Called every frame
void AAINPC::Tick(float DeltaTime)
{
	

	Super::Tick(DeltaTime);
	//Debug("%f", timeAttack);
	if (isEnemyAttacking && willAttack)
	{
		

		if (timeAttack > 0 && timeAttack < 45)
		{
			FTimerHandle TimerHandle;

			FVector TraceStart = GetMesh()->GetSocketLocation("TraceStart");
			FVector TraceEnd = GetMesh()->GetSocketLocation("TraceEnd");
			FHitResult HitResult;
			FCollisionQueryParams TraceParam;
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0, 1);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel3, TraceParam) )
			{
				//Debug("bat");
				if (!Ignore)
				{
					Ignore = true;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
						{
							willAttack = false;
							isEnemyAttacking = false;
							Ignore = false;
							AGladiatorGameModeBase* GameMode = Cast<AGladiatorGameModeBase>(UGameplayStatics::GetGameMode(this));
							GameMode->enemyIsAttacking = false;
						}, 0.8, false);
					//if (HitResult.Actor->IsA<ACharacter>())
					//Debug("coll");
				}
			
			}
			else if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel2, TraceParam) )
			{
				//Debug("player");
				if (!Ignore)
				{
					
					Ignore = true;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
						{
							willAttack = false;
							isEnemyAttacking = false;
							Ignore = false;
							AGladiatorGameModeBase* GameMode = Cast<AGladiatorGameModeBase>(UGameplayStatics::GetGameMode(this));
							GameMode->enemyIsAttacking = false;
						}, 0.8, false);

					if (APlayerGladiator* Character = Cast<APlayerGladiator>(HitResult.Actor))
					{
						Character->ApplyDamage(1);
					}
				}
				//if (HitResult.Actor->IsA<ACharacter>())
				//Debug("coll");


			}
			else if (timeAttack > 100)
			{
				timeAttack = 0;
				{
					Ignore = true;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
						{
							willAttack = false;
							isEnemyAttacking = false;
							Ignore = false;
							AGladiatorGameModeBase* GameMode = Cast<AGladiatorGameModeBase>(UGameplayStatics::GetGameMode(this));
							GameMode->enemyIsAttacking = false;
						}, 0.8, false);
					//if (HitResult.Actor->IsA<ACharacter>())
					//Debug("coll");
				}

			}
		}
		
		
		
	}
	else
	{
		timeAttack = 0;
	}
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
	if (Health <= 0 && !isDead)
	{
		isDead = true;
		GetMesh()->SetAnimation(death);
		GetMesh()->PlayAnimation(death, false);
		SetActorEnableCollision(false);
		AGladiatorGameModeBase* GameMode = Cast<AGladiatorGameModeBase>(UGameplayStatics::GetGameMode(this));
		if(isChasing)
		{
			GameMode->ChasingEnemies.Remove(this);
		}
		if (GameMode->enemyIsAttacking || willAttack)
		{
			GameMode->enemyIsAttacking = false;
		}

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

void AAINPC::Timer()
{
	timeAttack++;
}
