// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightBulb_3.h"

void AMyLightBulb_3::SetColorBehavior(float Value)
{
	if (Value > 0.99)
		Color_1 = FLinearColor::MakeRandomColor();
	else if (Value < 0.011)
		Color_1 = FLinearColor::MakeRandomColor();

	ColorEmissive = FMath::Lerp(Color_1, Color_2, Value);
}
