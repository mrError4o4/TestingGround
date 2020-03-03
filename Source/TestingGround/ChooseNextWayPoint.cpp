// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGround.h"
#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboardcomp = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboardcomp->GetValueAsInt(IndexKey.SelectedKeyName);
	//UE_LOG(LogTemp, Warning, TEXT("Way Point index: %i"), Index);
	return EBTNodeResult::Succeeded;
}