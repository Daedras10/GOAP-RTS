// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Structs.h"

bool FWMWorldStates::HasState(FString Key)
{
	return WorldStates.Contains(Key);
}

void FWMWorldStates::AddState(FString Key, int Value)
{
	WorldStates.Add(Key, Value);
}

void FWMWorldStates::SetState(FString Key, int Value)
{
	if (WorldStates.Contains(Key)) WorldStates[Key] = Value;
	else WorldStates.Add(Key, Value);
}

void FWMWorldStates::ModifyState(FString Key, int ValueToAdd)
{
	if (!WorldStates.Contains(Key)) WorldStates.Add(Key, ValueToAdd);
	else WorldStates[Key] += ValueToAdd;
	if (WorldStates[Key] <= 0) RemoveState(Key);
}

void FWMWorldStates::RemoveState(FString Key)
{
	WorldStates.Remove(Key);
}

TMap<FString, int> FWMWorldStates::GetStates()
{
	return WorldStates;
}
