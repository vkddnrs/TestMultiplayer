// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightBulb.h"
#include "MyLightBulb_3.generated.h"

/**
 * 
 */
UCLASS()
class TESTMULTIPLAYER_API AMyLightBulb_3 : public ALightBulb
{
	GENERATED_BODY()

protected:
	void SetColorBehavior(float Value) override;
};
