// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

void UHealthBar::NativeConstruct()
{
}

void UHealthBar::setBarValuePercent(float const value)
{
	healthValue->SetPercent(value);
}
