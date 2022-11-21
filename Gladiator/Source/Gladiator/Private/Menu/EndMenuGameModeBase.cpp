// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/EndMenuGameModeBase.h"

#include "Menu/StartMenuController.h"
#include "Menu/EndMenuHUD.h"

AEndMenuGameModeBase::AEndMenuGameModeBase()
{
	HUDClass = AEndMenuHUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStartMenuController::StaticClass();
}