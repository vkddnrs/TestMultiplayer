// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulb.h"

// Sets default values
ALightBulb::ALightBulb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

