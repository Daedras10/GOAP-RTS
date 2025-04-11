// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubGoal.generated.h"

struct FWMWorldState;
/**
 * 
 */
UCLASS()
class WAROFSINS_API USubGoal : public UObject
{
	GENERATED_BODY()

public:
	USubGoal();

	void Init(FString s, int i, bool r);

public:
	TMap<FString, int> SubGoals;
	UPROPERTY(EditAnywhere) bool bRemove;
	UPROPERTY(EditAnywhere) TArray<FWMWorldState> DebugInfo = TArray<FWMWorldState>();
};
