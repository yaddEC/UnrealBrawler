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
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
		UStaticMeshComponent* block_cube;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* animBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimSequence* death;
public:
	APlayerGladiator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		UMaterialInstanceDynamic* DynamicMaterial6;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		USkeletalMeshComponent* player;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material1;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material2;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material3;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material4;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material5;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
		UMaterialInterface* Material6;

	UPROPERTY(EditAnywhere, Category = "State")
		float hitColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool gotHit;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool isDead;
	UPROPERTY(EditAnywhere, Category = State)
		float MaxHealth;
	UPROPERTY(EditAnywhere, Category = State)
		float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
		FTimerHandle MemberTimerHandle;
	void ApplyDamage(float Damage);

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Attack();
	void Block();
	void Unblock();
	void Walk();
	void StopWalk();

	void GameOver();
	void Timer();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	class UWidgetComponent* WidgetComponent;
};
