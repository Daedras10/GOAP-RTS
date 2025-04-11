// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/Planner.h"

#include "GOAP/GoapNode.h"
#include "GOAP/Actions/GoapAction.h"


UPlanner::UPlanner()
{
}

TArray<UGoapAction*> UPlanner::Plan(TMap<FString, int> StartState, TMap<FString, int> GoalState,
                                    TArray<UGoapAction*> Actions)
{
	TArray<UGoapAction*> UsableActions = TArray<UGoapAction*>();
	for (UGoapAction* Action : Actions)
	{
		if (Action->IsAchievable(StartState))
		{
			UsableActions.Add(Action);
		}
	}

	TArray<UGoapNode*> Leaves = TArray<UGoapNode*>();
	UGoapNode* Start = NewObject<UGoapNode>();
	Start->Init(nullptr, 0, StartState, nullptr);

	bool Success = BuildGraph(Start, Leaves, Actions, GoalState);
	if (!Success)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Failed to build graph (%d goals with %d actions)"), GoalState.Num(), UsableActions.Num()));
		UE_LOG(LogTemp, Warning, TEXT("Failed to build graph (%d goals with %d actions)"), GoalState.Num(), UsableActions.Num());
		for (auto [Key, Value] : GoalState)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Goal: %s, %d"), *Key, Value));
			UE_LOG(LogTemp, Warning, TEXT("Goal: %s, %d"), *Key, Value);
		}
		for (UGoapAction* Action : UsableActions)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Action->GetActionName());
			UE_LOG(LogTemp, Warning, TEXT("Action: %s"), *Action->GetActionName());
			for (auto [Key, Value] : Action->GetPreconditions())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Precondition: %s, %d"), *Key, Value));
				UE_LOG(LogTemp, Warning, TEXT("Precondition: %s, %d"), *Key, Value);
			}
			for (auto [Key, Value] : Action->GetEffects())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Effect: %s, %d"), *Key, Value));
				UE_LOG(LogTemp, Warning, TEXT("Effect: %s, %d"), *Key, Value);
			}
		}
		return TArray<UGoapAction*>();
	}

	UGoapNode* Cheapest = nullptr;
	for (UGoapNode* Leaf : Leaves)
	{
		if (Cheapest == nullptr)
		{
			Cheapest = Leaf;
			continue;
		}
		if (Leaf->GetRunningCost() >= Cheapest->GetRunningCost()) continue;
		Cheapest = Leaf;
	}

	TArray<UGoapAction*> Result = TArray<UGoapAction*>();
	UGoapNode* Node = Cheapest;
	while (Node != nullptr)
	{
		if (Node->GetAction() != nullptr)
		{
			Result.Add(Node->GetAction());
		}
		Node = Node->GetParent();
	}
	TArray<UGoapAction*> Queue = TArray<UGoapAction*>();
	for (int i = Result.Num() - 1; i >= 0; i--)
	{
		Queue.Add(Result[i]);
	}

	if (bDebugPlan)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Plan found"));
		UE_LOG(LogTemp, Warning, TEXT("Plan found"));
		for (UGoapAction* Action : Queue)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, Action->GetActionName());
			UE_LOG(LogTemp, Warning, TEXT("Action: %s"), *Action->GetActionName());
		}
	}

	return Queue;
}

bool UPlanner::BuildGraph(UGoapNode* Start, TArray<UGoapNode*>& Leaves, TArray<UGoapAction*> UsableActions,
	TMap<FString, int> GoalState, int Depth)
{
	bool FoundPath = false;
	if (Depth > MaxDepth) return false;
	for (UGoapAction* Action : UsableActions)
	{
		if (Action->IsAchievable(Start->GetState()))
		{
			TMap<FString, int> CurrentState = TMap<FString, int>(Start->GetState());
			for (auto [Key, Value] : Action->GetEffects())
			{
				// if (CurrentState.Contains(Key)) CurrentState[Key] = Value;
				// else CurrentState.Add(Key, Value);

				if (!CurrentState.Contains(Key)) CurrentState.Add(Key, Value);
				else CurrentState[Key] += Value; // Was not in the original code, but it makes sense to add it
			}
			UGoapNode* Node = NewObject<UGoapNode>();
			Node->Init(Start, Start->GetRunningCost() + Action->GetCost(), CurrentState, Action);

			if (GoalAchieved(GoalState, CurrentState))
			{
				Leaves.Add(Node);
				FoundPath = true;
			}
			else
			{
				//TArray<UGoapAction*> UsableActionsCopy = ActionSubset(UsableActions, Action);
				bool Found = BuildGraph(Node, Leaves, UsableActions, GoalState, Depth + 1);
				if (Found) FoundPath = true;
			}
		}
	}
	return FoundPath;
}

bool UPlanner::GoalAchieved(TMap<FString, int> GoalState, TMap<FString, int> CurrentState)
{
	for (auto [Key, Value] : GoalState)
	{
		if (!CurrentState.Contains(Key) || CurrentState[Key] < Value) return false;
	}
	return true;
}

TArray<UGoapAction*> UPlanner::ActionSubset(TArray<UGoapAction*> Actions, const UGoapAction* RemoveMe)
{
	TArray<UGoapAction*> Subset = TArray<UGoapAction*>();
	for (UGoapAction* Action : Actions)
	{
		if (Action != RemoveMe) Subset.Add(Action);
		//else delete Action;
		///* Let's free the memory of the removed action */
		// Since it's a UObject, we can't do it like this xD
	}
	return Subset;
}
