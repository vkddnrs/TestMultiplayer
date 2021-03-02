// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Components/TimelineComponent.h"
#include "LightBulb.generated.h"


UCLASS()
class TESTMULTIPLAYER_API ALightBulb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightBulb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Replicated)
	class ALight* Target;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	FLinearColor Color_1 = FLinearColor(1,1,1);

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	FLinearColor Color_2 = FLinearColor(0, 0, 0);

public:
	//UPROPERTY(BlueprintReadWrite, Category = "DynamicMaterial")
	//UMaterialInstanceDynamic* matInstanceIndex_0;	

	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
	void OnLightEvent();

	UFUNCTION()// BlueprintNativeEvent, BlueprintCallable, Category = "LightControl")
	void OnLight();

	UFUNCTION()//BlueprintNativeEvent, BlueprintCallable, Category = "LightControl")
	void OffLight();

	FTimeline CurveTimeline;

protected:
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRepColorEmissive, Category = "Settings")
		FLinearColor ColorEmissive;

	UPROPERTY(EditAnywhere, Category = "Timeline");
		UCurveFloat* CurveFloat;

	UFUNCTION(BlueprintImplementableEvent, Category = "EventRep")
		void OnRepColorEmissive();
	
	void ColorModulate();
	
	UFUNCTION()
	void TimelineProgress(float Value);
	


};
