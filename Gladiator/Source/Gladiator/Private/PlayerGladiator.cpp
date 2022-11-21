// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGladiator.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HealthBar.h"
#include "Enemy/AINPC.h"
#include "Sound/SoundBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
APlayerGladiator::APlayerGladiator()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	isWalking = false;
	canAttack = true;
	MaxHealth = 5;
	Health = MaxHealth;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;


	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	FName weaponSocketName = TEXT("BatSocket");




	bat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bat_mesh"));
	bat->AttachTo(GetMesh(), weaponSocketName, EAttachLocation::SnapToTarget, true);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;

	block_cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("block_mesh"));
	block_cube->SetupAttachment(bat);



	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = false;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 85.f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widgetClass(TEXT("/Game/UI/HealthBarBP"));
		if (widgetClass.Succeeded())
		{
			WidgetComponent->SetWidgetClass(widgetClass.Class);
		}
	}

}

void APlayerGladiator::BeginPlay()
{
	Super::BeginPlay();

	player = GetMesh();
	if (player)
	{
		Material1 = player->GetMaterial(0);
		Material2 = player->GetMaterial(1);
		Material3 = player->GetMaterial(2);
		Material4 = player->GetMaterial(3);
		Material5 = player->GetMaterial(4);
		Material6 = player->GetMaterial(5);
		DynamicMaterial1 = UMaterialInstanceDynamic::Create(Material1, NULL);
		DynamicMaterial2 = UMaterialInstanceDynamic::Create(Material2, NULL);
		DynamicMaterial3 = UMaterialInstanceDynamic::Create(Material3, NULL);
		DynamicMaterial4 = UMaterialInstanceDynamic::Create(Material4, NULL);
		DynamicMaterial5 = UMaterialInstanceDynamic::Create(Material5, NULL);
		DynamicMaterial6 = UMaterialInstanceDynamic::Create(Material6, NULL);
		player->SetMaterial(0, DynamicMaterial1);
		player->SetMaterial(1, DynamicMaterial2);
		player->SetMaterial(2, DynamicMaterial3);
		player->SetMaterial(3, DynamicMaterial4);
		player->SetMaterial(4, DynamicMaterial5);
		player->SetMaterial(5, DynamicMaterial6);
	}

}


void APlayerGladiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//auto const uw = Cast<UHealthBar>(WidgetComponent->GetUserWidgetObject());
	//Debug("%f",Health);
	if (isAttacking)
	{

		canAttack = false;
		FTimerHandle TimerHandle;
		if (timeAttack > 48 && timeAttack < 65)
		{
			FVector TraceStart = bat->GetSocketLocation("TraceStart");
			FVector TraceEnd = bat->GetSocketLocation("TraceEnd");
			FHitResult HitResult;
			FCollisionQueryParams TraceParam;
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0, 1);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel1, TraceParam))
			{
				//if (HitResult.Actor->IsA<ACharacter>())
				//Debug("coll");
				if (AAINPC* Character = Cast<AAINPC>(HitResult.Actor))
				{
					Character->ApplyDamage(1);
				}

			}
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				canAttack = true;
			}, 1.2, false);

	}
	else
	{
		timeAttack = 0;
	}

	/*if (uw)
	{
		uw->setBarValuePercent(Health / MaxHealth);
	}*/

	if (Health <= 0 && !isDead)
	{
		isDead = true;
		GetMesh()->SetAnimation(death);
		GetMesh()->PlayAnimation(death, false);
		SetActorEnableCollision(false);
		UGameplayStatics::SpawnSoundAtLocation(this, deathSound, GetActorLocation());
	}
	if (gotHit && hitColor <= 0)
	{
		DynamicMaterial1->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial2->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial3->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial4->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial5->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial6->SetScalarParameterValue(TEXT("Blend"), hitColor);
		hitColor = 1;
		Debug("mat = %f", hitColor);
	}
	else if (hitColor > 0)
	{
		DynamicMaterial1->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial2->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial3->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial4->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial5->SetScalarParameterValue(TEXT("Blend"), hitColor);
		DynamicMaterial6->SetScalarParameterValue(TEXT("Blend"), hitColor);
		hitColor -= 0.01f;
		if (hitColor < 0.01f && gotHit)
			hitColor = 0.01f;
		Debug("mat = %f", hitColor);
	}
}

void APlayerGladiator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerGladiator::Attack);
	PlayerInputComponent->BindAction("Walking", IE_Pressed, this, &APlayerGladiator::Walk);
	PlayerInputComponent->BindAction("Walking", IE_Released, this, &APlayerGladiator::StopWalk);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &APlayerGladiator::Block);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &APlayerGladiator::Unblock);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerGladiator::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerGladiator::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerGladiator::Timer()
{
	timeAttack++;
}


void APlayerGladiator::Attack()
{
	if (!isDead && !isBlocking && !isAttacking && canAttack)
	{

		isAttacking = true;
		UGameplayStatics::SpawnSoundAtLocation(this, swingSound, GetActorLocation());
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				isAttacking = false;
			}, 1, false);

		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &APlayerGladiator::Timer, 0.01f, true, 0.0f);
	}
}

void APlayerGladiator::Block()
{
	if (!isDead && !isBlocking && !isAttacking)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		isBlocking = true;
		block_cube->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);

	}
}

void APlayerGladiator::Walk()
{
	isWalking = true;
}

void APlayerGladiator::StopWalk()
{
	isWalking = false;
}

void APlayerGladiator::Unblock()
{
	isBlocking = false;
	block_cube->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
}

void APlayerGladiator::MoveRight(float Axis)
{
	float speed;
	if (isWalking)
		speed = 0.5f;
	else
		speed = 1;
	if (!isDead && !isBlocking && !isAttacking)
	{
		AddMovementInput(FollowCamera->GetRightVector() * Axis * speed);
	}
}

void APlayerGladiator::MoveForward(float Axis)
{

	float speed;
	if (isWalking)
		speed = 0.5f;
	else
		speed = 1;
	if (!isDead && !isBlocking && !isAttacking)
	{
		AddMovementInput(FollowCamera->GetForwardVector() * Axis * speed);
	}


}

void APlayerGladiator::ApplyDamage(float Damage)
{
	if (!gotHit)
	{
		
		DynamicMaterial1 = UMaterialInstanceDynamic::Create(Material1, NULL);
		DynamicMaterial2 = UMaterialInstanceDynamic::Create(Material2, NULL);
		DynamicMaterial3 = UMaterialInstanceDynamic::Create(Material3, NULL);
		DynamicMaterial4 = UMaterialInstanceDynamic::Create(Material4, NULL);
		DynamicMaterial5 = UMaterialInstanceDynamic::Create(Material5, NULL);
		DynamicMaterial6 = UMaterialInstanceDynamic::Create(Material6, NULL);
		player->SetMaterial(0, DynamicMaterial1);
		player->SetMaterial(1, DynamicMaterial2);
		player->SetMaterial(2, DynamicMaterial3);
		player->SetMaterial(3, DynamicMaterial4);
		player->SetMaterial(4, DynamicMaterial5);
		player->SetMaterial(5, DynamicMaterial6);
		gotHit = true;
		Health -= Damage;
		if(Health>0)
			UGameplayStatics::SpawnSoundAtLocation(this, painSound, GetActorLocation());
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				gotHit = false;
			}, 1, false);
	}
}

