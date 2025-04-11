// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/SubGoal.h"

#include "Utils/Structs.h"

USubGoal::USubGoal()
{
	bRemove = false;
}

void USubGoal::Init(FString s, int i, bool r)
{
	SubGoals.Add(s, i);
	bRemove = r;
	DebugInfo.Add(FWMWorldState(s, i));
}
