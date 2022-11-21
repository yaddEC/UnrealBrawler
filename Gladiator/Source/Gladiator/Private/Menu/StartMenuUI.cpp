// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/StartMenuUI.h"

#include "Kismet/GameplayStatics.h"

void UStartMenuUI::NativeConstruct()
{
	if(playButton)
	{
		playButton->OnClicked.AddDynamic(this, &UStartMenuUI::PlayButtonClicked);
	}
	if(exitButton)
	{
		exitButton->OnClicked.AddDynamic(this, &UStartMenuUI::ExitButtonClicked);
	}
}

void UStartMenuUI::PlayButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Arene");
}

void UStartMenuUI::ExitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
