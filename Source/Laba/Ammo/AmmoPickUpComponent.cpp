// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUpComponent.h"

UAmmoPickUpComponent::UAmmoPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UAmmoPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UAmmoPickUpComponent::OnSphereBeginOverlap);
}

void UAmmoPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AAmmoCharacter* Character = Cast<AAmmoCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		AmmoOnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
