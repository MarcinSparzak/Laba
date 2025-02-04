// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindNextPathPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPath.h"

UBTTask_FindNextPathPoint::UBTTask_FindNextPathPoint()
{
	NodeName = TEXT("Find Next Path Point");
}

EBTNodeResult::Type UBTTask_FindNextPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    APatrolPath* Path = Cast<APatrolPath>(Blackboard->GetValueAsObject(TEXT("PatrolPath")));

    if (Path != nullptr)
    {
        int index = Blackboard->GetValueAsInt(TEXT("PatrolPointIndex"));
        

        UE_LOG(LogTemp, Warning, TEXT("Index %d"), index);
        FVector PathPoint = Path->PathPoints[index];
        UE_LOG(LogTemp, Warning, TEXT("PathPoint %s"), *PathPoint.ToString());
        FVector PathPointLocation = Path->GetActorLocation() + PathPoint;
        UE_LOG(LogTemp, Warning, TEXT("PathPointLocation: %s"), *PathPointLocation.ToString());

        Blackboard->SetValueAsVector("NextPatrolPoint", PathPointLocation);

        // Wyznaczenie nastêpnego punktu œcie¿ki
        bool IsBackNForthMovement = Blackboard->GetValueAsBool(TEXT("IsBackNForthMovement"));
        int length = Path->PathPoints.Num();

        if (IsBackNForthMovement)
        {
            bool IsMovingForward = Blackboard->GetValueAsBool(TEXT("IsMovingForward"));
            if (IsMovingForward)
            {
                if (index+1 < length)
                {
                    ++index;
                }
                else
                {
                    --index;
                    Blackboard->SetValueAsBool(TEXT("IsMovingForward"), false);
                }
            }
            else
            {
                if (index)
                {
                    --index;
                }
                else
                {
                    ++index;
                    Blackboard->SetValueAsBool(TEXT("IsMovingForward"), true);
                }
            }
        }
        else
        {
            index+1 < length ? ++index : index = 0;
        }
        Blackboard->SetValueAsInt("PatrolPointIndex", index);
    }
    else
    {

        UE_LOG(LogTemp, Warning, TEXT("Path not found"));
    }

    return EBTNodeResult::Type();
}
