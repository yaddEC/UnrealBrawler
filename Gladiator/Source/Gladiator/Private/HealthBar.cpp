// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"


void UHealthBar::SetHealth(float CurrentHealth, float MaxHealth)
{
	if(HealthBar)
		HealthBar->SetPercent(CurrentHealth/MaxHealth);
}
