// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WinMenuHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AWinMenuHUD::AWinMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/WinMenuBP"));
	if(ui.Succeeded())
	{
		uiBPclass = ui.Class;
	}
}

void AWinMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if(uiBPclass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPclass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}