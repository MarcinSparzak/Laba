// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuardCharacter.generated.h"

class APatrolPath;

UCLASS()
class LABA_API AGuardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGuardCharacter();

	UPROPERTY(EditInstanceOnly, Category = "AI|Patrolling")
	bool IsPatrolling;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	APatrolPath* PatrolPath;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	float DefaultWaitTime = 0.0f;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	float RandomDeviation = 0.0f;

	UPROPERTY(EditInstanceOnly, meta = (EditCondition = "IsPatrolling", Category = "AI|Patrolling"))
	bool IsBackNForthMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
