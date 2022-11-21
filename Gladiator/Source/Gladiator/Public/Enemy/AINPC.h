// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AINPC.generated.h"
#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}
class UMaterialInstanceDynamic;

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

	void ApplyDamage(float Damage);

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* deathSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* impactSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* guardSound;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
		USkeletalMeshComponent* enemy;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, Category = "State")
		float hitColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool willAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool isEnemyAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool MovOry;

	UPROPERTY(EditAnywhere, Category = State)
		float Health;
	
	UPROPERTY(EditAnywhere, Category = State)
	bool isDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool gotHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool isChasing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* death;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool Ignore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		float timeAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		FTimerHandle MemberTimerHandle;
private:
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setupStimulus();
	void Timer();


};
