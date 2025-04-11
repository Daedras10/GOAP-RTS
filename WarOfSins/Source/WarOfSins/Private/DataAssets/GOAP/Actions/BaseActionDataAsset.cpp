// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/GOAP/Actions/BaseActionDataAsset.h"

#include "Utils/Structs.h"

bool UBaseActionDataAsset::IsAchievable(TMap<FString, int> WorldStates)
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

bool UBaseActionDataAsset::PrePerformAction()
{
	return true;
}

bool UBaseActionDataAsset::PostPerformAction()
{
	return true;
}
