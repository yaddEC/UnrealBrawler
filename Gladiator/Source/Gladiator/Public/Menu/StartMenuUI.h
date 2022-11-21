// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* playButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* exitButton = nullptr;

private:
	UFUNCTION()
	void PlayButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
};
