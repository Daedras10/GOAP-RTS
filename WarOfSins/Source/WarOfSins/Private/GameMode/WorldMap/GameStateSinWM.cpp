// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/WorldMap/GameStateSinWM.h"
#include "Utils/Structs.h"

AGameStateSinWM::AGameStateSinWM()
{
	WorldStates = new FWMWorldStates();
}

FWMWorldStates* AGameStateSinWM::GetWorldStates()
{
	return WorldStates;
}
