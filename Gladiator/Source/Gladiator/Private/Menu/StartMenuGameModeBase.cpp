// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/StartMenuGameModeBase.h"

#include "Menu/StartMenuController.h"
#include "Menu/StartMenuHUD.h"

AStartMenuGameModeBase::AStartMenuGameModeBase()
{
	HUDClass = AStartMenuHUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStartMenuController::StaticClass();
}
