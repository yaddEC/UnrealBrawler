// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GLADIATOR_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float CurrentHealth, float MaxHealth);

protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;
	
};
