// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "CollisionShape.h"
#include "GeneratedCodeHelpers.h"


// Sets default values
APlate::APlate()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = Box;
	Box->InitBoxExtent(FVector(100, 100, 20));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent); //AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true));
	PlayerName = FString();
}


// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &APlate::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APlate::OnEndOverlap);

}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlate::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlate, Target);
	DOREPLIFETIME(APlate, PlayerName);
}

void APlate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())		
	{
		PlayerName = OtherActor->GetActorLabel(); // � �������� ��� ��� �� ������		
		if(!PlayerNameList.Contains(OtherActor->GetActorLabel())) // ���� � ������ ��� ����� ����, ��� ������ �� �����
			PlayerNameList.Add(OtherActor->GetActorLabel()); // ������� ��� � ������		
			
		for (int i = 0; i < LightBulbList.Num(); i++)
			LightBulbList[i]->OnLight(); // �������� ��������
	}	
}

void APlate::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerNameList.Contains(OtherActor->GetActorLabel()))
		PlayerNameList.Remove(OtherActor->GetActorLabel());

	EndOverlap(); // �������� � ��������� ������� � ������ �� �������
	PlayerName = FString();	// ������ � ����� ������������������!! ��� ��������� �������� �������

	if (PlayerNameList.Num())
		if (HasAuthority())
			PlayerName = PlayerNameList.Top(); // ��������� ������ � ������ ���� �����, ������� ������� �� �����

	if (!PlayerNameList.Num()) // ���� �� ����� ������ �� �������� - ����� ��������
		for (int i = 0; i < LightBulbList.Num(); i++)
			LightBulbList[i]->OffLight();
}


