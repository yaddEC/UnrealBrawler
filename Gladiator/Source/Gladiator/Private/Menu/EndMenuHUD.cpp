// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/EndMenuHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AEndMenuHUD::AEndMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/UI/EndMenuBP"));
	if(ui.Succeeded())
	{
		uiBPclass = ui.Class;
	}
}

void AEndMenuHUD::BeginPlay()
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

