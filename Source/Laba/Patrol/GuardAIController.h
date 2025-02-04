// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardAIController.generated.h"


class AGuardCharacter;
/**
 * 
 */
UCLASS()
class LABA_API AGuardAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;

	AGuardCharacter* GuardCharacter;

	void SetupBlackboard();
	
};
