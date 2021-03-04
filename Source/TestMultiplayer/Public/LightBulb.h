// Базовый класс для всех Лампочек

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Components/TimelineComponent.h"
#include "LightBulb.generated.h"

class UCurveFloat;

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
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		FLinearColor Color_1;
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		FLinearColor Color_2;

	UPROPERTY(BlueprintReadOnly, Category = "light")
		bool IsLighting = false;
	

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		void OnLightEvent();
	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		void OffLightEvent();

	UFUNCTION()
	void OnLight();

	UFUNCTION()
	void OffLight();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRepColor, Category = "Settings")
		FLinearColor ColorEmissive;
	UFUNCTION(BlueprintImplementableEvent, Category = "EventRep")
		void OnRepColor();

protected:
	//***** Timeline
	FTimeline CurveTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline");
		UCurveFloat* CurveFloat;	
	void ColorModulate();
	
	UFUNCTION()
	virtual void SetColorBehavior(float Value); 
	// Переопределение этого метода дает возможность
	// задать другое поведение лампочке класса-наследника
	//**********
	

};
