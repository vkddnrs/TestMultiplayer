// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LightBulb.h"
#include "Plate.generated.h"


UCLASS()
class TESTMULTIPLAYER_API APlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSupportedForNetworking() const override	{return true;}
	
protected:
	//************ Репликация***************
	UPROPERTY(Replicated)
		class ALight* Target;
	// включаем репликацию объекта и его составляющих
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	//**************************************
	// Коллизия
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "CastomEvent")
		// Эвент для блюпринта
		void EndOverlap();

	UPROPERTY(EditAnywhere, Category="Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Box")
		UBoxComponent* Box;

	//**************** Вывод имени перса***************
	UPROPERTY(ReplicatedUsing = PullMessage, BlueprintReadOnly, Category="PlayerName")
	FString PlayerName;

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		// реплицирует на клиент смену имени перса
		void PullMessage();

	TArray<FString> PlayerNameList;
	//***************************************************

	UPROPERTY(EditAnywhere, Category = "LightBulbs")
		TArray<TAssetPtr<ALightBulb>> LightBulbList; // массив наших лампочек
	
	UPROPERTY(EditAnywhere)
		TAssetPtr<AActor> Floor; // пол на уровне

	
};

