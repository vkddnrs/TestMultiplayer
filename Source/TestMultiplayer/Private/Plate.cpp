// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "CollisionShape.h"
#include "GeneratedCodeHelpers.h"
//#include "Kismet/GameplayStatics.h"

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
	//Mesh->AddLocalOffset(FVector());
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

void APlate::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlate, Target);
}

void APlate::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	#if UE_SERVER //  этот способ здесь не работает - только на выделенном серваке будет работать
		PlayerName = OtherActor->GetActorLabel();
	#endif

	PlayerName = OtherActor->GetActorLabel();
  }

void APlate::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerName = FString();
}

FString APlate::PullMessage_Implementation(FString& actor_name)
{
	return actor_name;
}