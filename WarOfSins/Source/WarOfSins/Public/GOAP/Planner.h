// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Planner.generated.h"

class UGoapNode;
class UGoapAction;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable)
class WAROFSINS_API UPlanner : public UObject
{
	GENERATED_BODY()
public:
	UPlanner();

	/* Is actually a TArray instead of a TQueue since TQueue is wierd */
	TArray<UGoapAction*> Plan(TMap<FString, int> StartState, TMap<FString, int> GoalState, TArray<UGoapAction*> Actions);
	bool BuildGraph(UGoapNode* Start, TArray<UGoapNode*>& Leaves, TArray<UGoapAction*> UsableActions, TMap<FString, int> GoalState, int Depth = 0);

	bool GoalAchieved(TMap<FString, int> GoalState, TMap<FString, int> CurrentState);
	TArray<UGoapAction*> ActionSubset(TArray<UGoapAction*> Actions, const UGoapAction* RemoveMe);

protected:
	bool bDebugPlan = true;
	int MaxDepth = 30;
};
