// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "TestingGround.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BTFunctionLibrary.h>

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the patrol route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	//Warn about empty patrol route
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty Patrol Points"))
		return EBTNodeResult::Failed;
	}

	//Set next waypoint
	auto Blackboardcomp = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboardcomp->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboardcomp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle points index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	Blackboardcomp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	return EBTNodeResult::Succeeded;
}