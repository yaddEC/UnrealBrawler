// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AINPC.generated.h"

UCLASS()
class GLADIATOR_API AAINPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAINPC();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
	bool isAttacking;

private:

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setupStimulus();

};
