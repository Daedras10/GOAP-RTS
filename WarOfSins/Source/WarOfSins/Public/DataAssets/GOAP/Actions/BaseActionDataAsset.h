// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Utils/Structs.h"
#include "BaseActionDataAsset.generated.h"
/**
 * 
 */
UCLASS()
class WAROFSINS_API UBaseActionDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	bool IsAchievable(TMap<FString, int> WorldStates);

	virtual bool PrePerformAction();
	virtual bool PostPerformAction();
	


protected:
	FString ActionName = "Action";
	int Cost = 1.0f;

	TArray<FWMWorldState> Preconditions = TArray<FWMWorldState>();
	TArray<FWMWorldState> Effects = TArray<FWMWorldState>();

	//TMap since they are easier to use, the other is just for the UI
};
