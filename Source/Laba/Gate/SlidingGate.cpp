// Fill out your copyright notice in the Description page of Project Settings.

#include "SlidingGate.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASlidingGate::ASlidingGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Stworzenie obiektu kapsu³y do wykrywania gdy gracz jest blisko drzwi
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Door Trigger"));
	SetRootComponent(CapsuleCollision);

	// Ustawienie parametrów kapsu³y
	CapsuleCollision->SetRelativeLocation(FVector(0, 0, 100));
	CapsuleCollision->SetCapsuleHalfHeight(285);
	CapsuleCollision->SetCapsuleRadius(200);

	// Ustawienie kolizji
	CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ASlidingGate::OpenGates);
	CapsuleCollision->OnComponentEndOverlap.AddDynamic(this, &ASlidingGate::CloseGates);

	// Wyszukanie assetu mesh dla drzwi
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));
	UStaticMesh* Asset = MeshAsset.Object;

	// Utworznie obiektu lewych drzwi
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));
	LeftDoor->SetStaticMesh(Asset);
	LeftDoor->SetupAttachment(CapsuleCollision);
	LeftDoor->SetRelativeLocation(FVector(0, 90,-100));
	LeftDoor->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	// Utworznie obiektu prawych drzwi
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));
	RightDoor->SetStaticMesh(Asset);
	RightDoor->SetupAttachment(CapsuleCollision);
	RightDoor->SetRelativeLocationAndRotation(FVector(0, -90, -100), FRotator(0, 180, 0));
	RightDoor->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	

	// Stworznie obiektu timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	
}

// Called when the game starts or when spawned
void ASlidingGate::BeginPlay()
{
	Super::BeginPlay();


	// Konfiguracja timeline
	TimelineCurve = NewObject<UCurveFloat>();
	TimelineCurve->FloatCurve.AddKey(0.0f, 0.0f);
	TimelineCurve->FloatCurve.AddKey(1.0f, 1.0f);
	TimelineProgress.BindUFunction(this, FName("TimelineProgressFunction"));
	DoorTimeline->SetTimelineLength(1.0f);
	DoorTimeline->AddInterpFloat(TimelineCurve, TimelineProgress);
}

// Called every frame
void ASlidingGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlidingGate::TimelineProgressFunction(float val)
{

	float slideProgress = val * DoorOffset;

	float lCurrentYPos = LRelativeYPosClosed + slideProgress;
	FVector newLDoorPos = LeftDoor->GetRelativeLocation();
	newLDoorPos.Y = lCurrentYPos;
	LeftDoor->SetRelativeLocation(newLDoorPos);
	
	float rCurrentYPos = RRelativeYPosClosed - slideProgress;
	FVector newRDoorPos = RightDoor->GetRelativeLocation();
	newRDoorPos.Y = rCurrentYPos;
	RightDoor->SetRelativeLocation(newRDoorPos);
}

void ASlidingGate::OpenGates(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	if (GetWorld()->GetTimerManager().IsTimerActive(CloseDelay))
	{
		GetWorld()->GetTimerManager().ClearTimer(CloseDelay);
	}
	DoorTimeline->Play();
}

void ASlidingGate::CloseGates(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

	GetWorld()->GetTimerManager().SetTimer(CloseDelay, [&]()
		{
			DoorTimeline->Reverse();
		}, 2, false);

}

