// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "CollisionShape.h"

// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = Box;
	Box->InitBoxExtent(FVector(100, 100, 20));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));

}


// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	//Box->OnComponentHit.AddDynamic(this, &APlate::OnHit);
	Box->OnComponentBeginOverlap.AddDynamic(this, &APlate::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APlate::OnEndOverlap);

}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorWorldOffset(FVector(0, 0, 10));

}

void APlate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	OtherActor->GetActorLabel();
}

void APlate::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}