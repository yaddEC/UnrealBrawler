// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGladiator.h"

// Sets default values
APlayerGladiator::APlayerGladiator()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerGladiator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerGladiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerGladiator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerGladiator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerGladiator::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerGladiator::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerGladiator::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerGladiator::Jump);
}

void APlayerGladiator::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector() * Axis);
}

void APlayerGladiator::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector() * Axis);
}


