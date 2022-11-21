// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StartMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class AStartMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	AStartMenuHUD();
	void BeginPlay() override;

private:

	TSubclassOf<class UUserWidget> uiBPclass;
	UUserWidget* uiWidget;
};
