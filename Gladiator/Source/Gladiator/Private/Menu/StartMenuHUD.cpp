// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/StartMenuHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AStartMenuHUD::AStartMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/StartMenuBP"));
	if(ui.Succeeded())
	{
		uiBPclass = ui.Class;
	}
}

void AStartMenuHUD::BeginPlay()
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
