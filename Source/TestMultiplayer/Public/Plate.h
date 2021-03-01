// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
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

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent, Category="Event")
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, Category = "Event")
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(replicated)
	class AActor* Target;

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
	
protected:
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Box")
	UBoxComponent* Box;

	UPROPERTY(Replicated, BlueprintReadOnly, Category="PlayerName")
	FString PlayerName;

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Event")
	FString PullMessage(FString& actor_name);	
};

