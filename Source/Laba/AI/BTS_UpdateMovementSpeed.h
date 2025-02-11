// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_UpdateMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class LABA_API UBTS_UpdateMovementSpeed : public UBTService
{
	GENERATED_BODY()
	
	UBTS_UpdateMovementSpeed();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float WalkSpeed = 0.0f;
};
