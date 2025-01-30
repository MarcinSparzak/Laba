// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SlidingGate.generated.h"

UCLASS()
class LABA_API ASlidingGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* RightDoor;

private:

	/*
		Funkcje i pola dotycz�ce timeline
	*/
	UPROPERTY()
	UTimelineComponent* DoorTimeline; // Timeline component
	UPROPERTY()
	UCurveFloat* TimelineCurve; // �cie�ka dla timeline

	FOnTimelineFloat TimelineProgress; // Obiekt w timeline kt�ry ma zawiera� funkcje wywo�ywan� na tick

	UFUNCTION()
	void TimelineProgressFunction(float val); // Funkcja wywo�ywana na tick timeline


	/*
		Funkcja wywo�ywana na rozpocz�cie Overlap
	*/
	UFUNCTION()
	void OpenGates(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	/*
		Funkcja wywo�ywana gdy Overlap si� ko�czy
	*/
	UFUNCTION()
	void CloseGates(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY()
	float DoorOffset = 100;
	UPROPERTY()
	float LRelativeYPosClosed = 90;
	UPROPERTY()
	float RRelativeYPosClosed = -90;

	UPROPERTY()
	FTimerHandle CloseDelay;
};
