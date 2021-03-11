// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightBulb.h"
#include "MyLightBulb_1.generated.h"

/**
 * 
 */
UCLASS()
class TESTMULTIPLAYER_API AMyLightBulb_1 : public ALightBulb
{
	GENERATED_BODY()

protected:
	// Переопределение этого метода дает возможность
	// задать лампочке данного класса поведение
	// отличное от того, что прописано в базовом классе
	void SetColorBehavior(float Value) override;

};
