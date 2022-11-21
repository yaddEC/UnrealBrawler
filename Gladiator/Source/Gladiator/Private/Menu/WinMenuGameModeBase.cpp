// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WinMenuGameModeBase.h"

#include "Menu/StartMenuController.h"
#include "Menu/WinMenuHUD.h"

AWinMenuGameModeBase::AWinMenuGameModeBase()
{
	HUDClass = AWinMenuHUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStartMenuController::StaticClass();
}