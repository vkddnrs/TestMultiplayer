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

// overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		// включение лампочки (интерфейс управления)
		void OnLight();
	UFUNCTION()
		// выключение лампочки(интерфейс управления)
		void OffLight();

protected:
	//************ Репликация***************
	UPROPERTY(Replicated)
		class ALight* Target;
	// включаем репликацию объекта и его составляющих
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	//**************************************

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		// используется для управления цветом материала лампы (начальный цвет)
		FLinearColor Color_1; 
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		// используется для управления цветом материала лампы
		FLinearColor Color_2;	
	UPROPERTY(BlueprintReadOnly, Category = "light")
		// используется для управления серверной частью в блюпринте
		bool IsLighting = false;	

	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		// активация процесса динамического изменения цвета материала лампочки в блюпринте на сервере
		void OnLightEvent();
	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		// дезактивация процесса динамического изменения цвета материала лампочки в блюпринте на сервере
		void OffLightEvent();
	
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRepColor, Category = "Settings")
		// цвет, передаваемый в блюпринт для динамического изменения цвета материала лампочки
		FLinearColor ColorEmissive;

	// реплицирует на клиент процесс управления цветом лампочки 
	UFUNCTION(BlueprintImplementableEvent, Category = "EventRep")
		void OnRepColor();

protected:
	//***** Timeline - анимация изменения цвета в переменной ColorEmissive
	FTimeline CurveTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline");
		// График, управляющий изменением переменной в таймлайне,
		// которая передаётся в SetColorBehavior
		UCurveFloat* CurveFloat;	

	// устанавливает параметры таймлайна и запускает его
	void SetTimeline();
	
	UFUNCTION()
	// Переопределение этого метода дает возможность
	// задать другое поведение лампочке класса-наследника
	virtual void SetColorBehavior(float Value); 

	//**********	

};
