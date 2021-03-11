// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulb.h"

#include "GeneratedCodeHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathVectorCommon.h"


class UCurveFloat;

// Sets default values
ALightBulb::ALightBulb()
{
	bReplicates = true;
	IsLighting = false;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Color_1 = FLinearColor(0, 0, 0);
	Color_2 = FLinearColor(0.5, 0, 0.5);
}

// Called when the game starts or when spawned
void ALightBulb::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightBulb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void ALightBulb::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALightBulb, Target);
	DOREPLIFETIME(ALightBulb, ColorEmissive);
}

void ALightBulb::OnLight()
{
	if (HasAuthority())
	{
		SetTimeline();
		OnLightEvent();
		IsLighting = true;
	}						
}

void ALightBulb::OffLight()
{
	if(HasAuthority())
	{
		CurveTimeline.Stop();
		OffLightEvent();		
		ColorEmissive = Color_2;
		IsLighting = false;		
	}	
}

void ALightBulb::SetTimeline()
{
	FLinearColor::MakeRandomColor();
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		// привязываем метод, в который будет передаваться изменяемая таймлайном переменная
		TimelineProgress.BindUFunction(this, FName("SetColorBehavior"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		CurveTimeline.PlayFromStart();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("CurveFloat for color management is not installed."))
}

void ALightBulb::SetColorBehavior(float Value)
{
	ColorEmissive = FMath::Lerp(Color_1, Color_2, Value);

	if(Value > 0.99)
		Color_1 = FLinearColor::MakeRandomColor();
	else if (Value < 0.011)
		Color_2 = FLinearColor::MakeRandomColor();
}

