// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGOAPState : uint8
{
	GOAPState_NotStarted,
	GOAPState_Running,
	GOAPState_Finished,
};
