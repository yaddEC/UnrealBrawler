// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}
#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "PlayerGladiator.generated.h"

UCLASS()
class GLADIATOR_API APlayerGladiator : public ACharacter
{
	GENERATED_BODY()



		UPROPERTY(EditAnywhere, Category = "Weapon")
		UStaticMeshComponent* bat;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* swing;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* block;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* animBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	APlayerGladiator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool isBlocking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool isAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		float timeAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool canAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		bool isWalking;
	UPROPERTY(EditAnywhere, Category = State)
		float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		FTimerHandle MemberTimerHandle;
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Attack();
	void Block();
	void Unblock();
	void Walk();
	void StopWalk();
	void ApplyDamage(float Damage);
	void Timer();
	void GameOver();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
