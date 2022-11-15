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

// Sets default values
APlayerGladiator::APlayerGladiator()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	isWalking = false;

	Health = 5;

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



	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 	
	CameraBoom->bUsePawnControlRotation = false; 

	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);



	

}

void APlayerGladiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isAttacking) 
	{
		FVector TraceStart = bat->GetSocketLocation("TraceStart");
		FVector TraceEnd = bat->GetSocketLocation("TraceEnd");
		FHitResult HitResult;
		FCollisionQueryParams TraceParam;
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0, 1);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel1, TraceParam))
		{
			//if (HitResult.Actor->IsA<ACharacter>())
				Debug("coll");
		}
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




void APlayerGladiator::Attack()
{
	if (!isBlocking && !isAttacking)
	{
		isAttacking = true;
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				isAttacking = false;
			}, 1, false);
	}
}

void APlayerGladiator::Block()
{
	if (!isBlocking && !isAttacking)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		isBlocking = true;
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
}

void APlayerGladiator::MoveRight(float Axis)
{
	float speed;
	if (isWalking)
		speed = 0.5f;
	else
		speed = 1;
	if (!isBlocking && !isAttacking)
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
	if (!isBlocking && !isAttacking)
	{
		AddMovementInput(FollowCamera->GetForwardVector() * Axis * speed);
	}


}

void APlayerGladiator::ApplyDamage(float Damage)
{
	Health -= Damage;
}

