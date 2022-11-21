// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WinMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AWinMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	AWinMenuHUD();
	void BeginPlay() override;

private:

	TSubclassOf<class UUserWidget> uiBPclass;
	UUserWidget* uiWidget;
	
};
