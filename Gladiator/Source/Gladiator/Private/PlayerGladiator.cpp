// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGladiator.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerGladiator::APlayerGladiator()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	
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


	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
			GetMesh()->SetWorldRotation(CurrentVelocity.ToOrientationRotator());
		}
	}
}

void APlayerGladiator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerGladiator::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerGladiator::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}


void APlayerGladiator::MoveForward(float Axis)
{
	
	AddMovementInput(FollowCamera->GetForwardVector() * Axis);
	//CurrentVelocity.Y = FMath::Clamp(-Axis, -1.0f, 1.0f);

}

void APlayerGladiator::MoveRight(float Axis)
{
	//CurrentVelocity.X = FMath::Clamp(Axis, -1.0f, 1.0f) ;
	AddMovementInput(FollowCamera->GetRightVector() * Axis);
}



