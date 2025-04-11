// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/Actions/GoapAction.h"

#include "Utils/Structs.h"

UGoapAction::UGoapAction()
{
}

bool UGoapAction::IsAchievable(TMap<FString, int> WorldStates)
{
	for (auto Precondition : Preconditions)
	{
		if (!WorldStates.Contains(Precondition.Key) || WorldStates[Precondition.Key] < Precondition.Value)
		{
			return false;
		}
	}
	return true;
}

bool UGoapAction::IsRunning()
{
	return State == EGOAPState::GOAPState_Running;
}

bool UGoapAction::IsFinished()
{
	return State == EGOAPState::GOAPState_Finished;
}

bool UGoapAction::PrePerformAction(AGOAPAgent* GoapAgent)
{
	State = EGOAPState::GOAPState_Running;
	return true;
}

bool UGoapAction::PostPerformAction(AGOAPAgent* GoapAgent)
{
	return true;
}

bool UGoapAction::Progress(float DeltaTime, AGOAPAgent* GoapAgent)
{
	State = EGOAPState::GOAPState_Finished;
	return true;
}

FString UGoapAction::GetActionName()
{
	return ActionName;
}

int UGoapAction::GetCost()
{
	return Cost;
}

TMap<FString, int> UGoapAction::GetPreconditions()
{
	return Preconditions;
}

TMap<FString, int> UGoapAction::GetEffects()
{
	return Effects;
}

// TArray<FWMWorldState> UGoapAction::GetPreconditionsStruct()
// {
// 	return PreconditionsStruct;
// }
//
// TArray<FWMWorldState> UGoapAction::GetEffectsStruct()
// {
// 	return EffectsStruct;
// }
