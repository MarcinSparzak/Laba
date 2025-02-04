// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GuardCharacter.h"
#include "PatrolPath.h"

void AGuardAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	GuardCharacter = Cast<AGuardCharacter>(GetPawn());
	if (GuardCharacter == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Character Found"));
		return;
	}

	if (AIBehaviorTree != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree"));
		RunBehaviorTree(AIBehaviorTree);
	}

	SetupBlackboard();
}

void AGuardAIController::SetupBlackboard()
{
	UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

	if (AIBlackboard == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard not found"));
		return;
	}

	AIBlackboard->SetValueAsBool(TEXT("IsPatrolling"), GuardCharacter->IsPatrolling);
	if (GuardCharacter->IsPatrolling)
	{
		AIBlackboard->SetValueAsInt(TEXT("PatrolPointIndex"), 0);
		AIBlackboard->SetValueAsObject(TEXT("PatrolPath"), GuardCharacter->PatrolPath);
		AIBlackboard->SetValueAsFloat(TEXT("DefaultWaitTime"), GuardCharacter->DefaultWaitTime);
		AIBlackboard->SetValueAsFloat(TEXT("RandomDeviation"), GuardCharacter->RandomDeviation);
		AIBlackboard->SetValueAsBool(TEXT("IsBackNForthMovement"), GuardCharacter->IsBackNForthMovement);
	}
}
