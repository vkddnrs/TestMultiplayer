// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightBulb_3.h"

void AMyLightBulb_3::SetColorBehavior(float Value)
{
	if (Value > 0.099)
	{
		Color_1 = Color_2;
		Color_2 = FLinearColor::MakeRandomColor();
	}

	ColorEmissive = FMath::Lerp(Color_1, Color_2, Value);
}
