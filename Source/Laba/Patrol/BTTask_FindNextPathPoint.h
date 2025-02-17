// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class LABA_API UBTTask_FindNextPathPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FindNextPathPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
