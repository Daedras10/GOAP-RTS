// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/TroopGatherer.h"

#include "GOAP/Actions/GoToRecruitmentCenterAction.h"
#include "GOAP/SubGoal.h"
#include "GOAP/Actions/RecruitAction.h"

ATroopGatherer::ATroopGatherer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATroopGatherer::AddTroops(int TroopToAdd)
{
	GathererCount += TroopToAdd;
}

void ATroopGatherer::BeginPlay()
{
	Super::BeginPlay();
	auto SubGoal = NewObject<USubGoal>();
	SubGoal->Init("Troops", 3, true);
	FSubGoalImportance SubGoalImportance = FSubGoalImportance(SubGoal, 1);
	Goals.Add(SubGoalImportance);


	/* Actions */
	auto GoToRecruitmentCenterAction = NewObject<UGoToRecruitmentCenterAction>();
	Actions.Add(GoToRecruitmentCenterAction);

	auto RecruitAction = NewObject<URecruitAction>();
	Actions.Add(RecruitAction);
}
