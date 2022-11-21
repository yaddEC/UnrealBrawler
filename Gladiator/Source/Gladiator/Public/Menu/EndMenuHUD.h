// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AEndMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	AEndMenuHUD();
	void BeginPlay() override;

private:

	TSubclassOf<class UUserWidget> uiBPclass;
	UUserWidget* uiWidget;
	
};
