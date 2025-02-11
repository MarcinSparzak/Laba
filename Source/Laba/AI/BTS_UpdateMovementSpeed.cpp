// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateMovementSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTS_UpdateMovementSpeed::UBTS_UpdateMovementSpeed()
{
	NodeName = TEXT("Update Movement Speed");
	bNotifyBecomeRelevant = true;
}

void UBTS_UpdateMovementSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetCharacter())
	{
		ACharacter* TargetCharacter = OwnerComp.GetAIOwner()->GetCharacter();
		UCharacterMovementComponent* MoveComp = TargetCharacter->GetCharacterMovement();
		MoveComp->MaxWalkSpeed = WalkSpeed;
	}

}
