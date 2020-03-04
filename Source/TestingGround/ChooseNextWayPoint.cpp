// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "TestingGround.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Runtime\AIModule\Classes\BehaviorTree\BTFunctionLibrary.h>

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the patrol points
	auto AIContoller = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIContoller->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Set next waypoint
	auto Blackboardcomp = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboardcomp->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboardcomp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle points index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	Blackboardcomp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	return EBTNodeResult::Succeeded;
}