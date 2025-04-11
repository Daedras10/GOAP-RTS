// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/Actions/RecruitAction.h"

#include "Testing/TroopGatherer.h"

URecruitAction::URecruitAction()
{
	ActionName = "RecruitTroops";
	Cost = 1;

	Preconditions.Add("AtRecruitmentCenter", 1);

	Effects.Add("Troops", 1);
	
	
}

bool URecruitAction::PrePerformAction(AGOAPAgent* GoapAgent)
{
	return Super::PrePerformAction(GoapAgent);
}

bool URecruitAction::PostPerformAction(AGOAPAgent* GoapAgent)
{
	return Super::PostPerformAction(GoapAgent);
}

bool URecruitAction::Progress(float DeltaTime, AGOAPAgent* GoapAgent)
{
	Super::Progress(DeltaTime, GoapAgent);
	if (State == EGOAPState::GOAPState_Finished) return true;

	RecruitmentTimer += DeltaTime;
	if (RecruitmentTimer >= RecruitmentTime)
	{
		State = EGOAPState::GOAPState_Finished;
		auto Gatherer = Cast<ATroopGatherer>(GoapAgent);
		if (Gatherer) Gatherer->AddTroops(1);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "Recruited 1 troop");
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Green, "Recruiting troops...");
	}

	return false;
}
