// ������� ����� ��� ���� ��������

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
		// ��������� �������� (��������� ����������)
		void OnLight();
	UFUNCTION()
		// ���������� ��������(��������� ����������)
		void OffLight();

protected:
	//************ ����������***************
	UPROPERTY(Replicated)
		class ALight* Target;
	// �������� ���������� ������� � ��� ������������
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	//**************************************

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		// ������������ ��� ���������� ������ ��������� ����� (��������� ����)
		FLinearColor Color_1; 
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
		// ������������ ��� ���������� ������ ��������� �����
		FLinearColor Color_2;	
	UPROPERTY(BlueprintReadOnly, Category = "light")
		// ������������ ��� ���������� ��������� ������ � ���������
		bool IsLighting = false;	

	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		// ��������� �������� ������������� ��������� ����� ��������� �������� � ��������� �� �������
		void OnLightEvent();
	UFUNCTION(BlueprintImplementableEvent, Category = "LightControl")
		// ������������ �������� ������������� ��������� ����� ��������� �������� � ��������� �� �������
		void OffLightEvent();
	
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRepColor, Category = "Settings")
		// ����, ������������ � �������� ��� ������������� ��������� ����� ��������� ��������
		FLinearColor ColorEmissive;

	// ����������� �� ������ ������� ���������� ������ �������� 
	UFUNCTION(BlueprintImplementableEvent, Category = "EventRep")
		void OnRepColor();

protected:
	//***** Timeline - �������� ��������� ����� � ���������� ColorEmissive
	FTimeline CurveTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline");
		// ������, ����������� ���������� ���������� � ���������,
		// ������� ��������� � SetColorBehavior
		UCurveFloat* CurveFloat;	

	// ������������� ��������� ��������� � ��������� ���
	void SetTimeline();
	
	UFUNCTION()
	// ��������������� ����� ������ ���� �����������
	// ������ ������ ��������� �������� ������-����������
	virtual void SetColorBehavior(float Value); 

	//**********	

};
