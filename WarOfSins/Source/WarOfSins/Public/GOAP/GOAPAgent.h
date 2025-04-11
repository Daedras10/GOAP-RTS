// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Planner.h"
#include "Actions/GoapAction.h"
#include "GameFramework/Character.h"
#include "GameMode/WorldMap/GameStateSinWM.h"
#include "Utils/Structs.h"
#include "GOAPAgent.generated.h"

/* TODO: Should be forward declarations but there were errors */

class USubGoal;

// USTRUCT()
// struct FSubGoal
// {
// 	GENERATED_BODY()
//
// 	TMap<FString, int> SubGoals;
// 	UPROPERTY(EditAnywhere) bool bRemove;
//
// 	FSubGoal()
// 	{
// 		SubGoals.Add("None", 0);
// 		bRemove = false;
// 	}
//
// 	FSubGoal(FString s, int i, bool r)
// 	{
// 		SubGoals.Add(s, i);
// 		bRemove = r;
// 	}
// };

USTRUCT()
struct FSubGoalImportance
{
	GENERATED_BODY()

	USubGoal* SubGoal;
	UPROPERTY(EditAnywhere) int Importance;

	FSubGoalImportance()
	{
		Importance = 0;
	}

	FSubGoalImportance(USubGoal* sg, int i)
	{
		SubGoal = sg;
		Importance = i;
	}
};


UCLASS()
class WAROFSINS_API AGOAPAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGOAPAgent();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	virtual void BeginPlay() override;

	void GoapTick(float DeltaTime);
	void RemoveGoalFromGoals(const USubGoal* Goal);

protected:
	UPROPERTY(EditAnywhere) UPlanner* Planner;
	UPROPERTY(EditAnywhere) TArray<UGoapAction*> Plan = TArray<UGoapAction*>();
	UPROPERTY(EditAnywhere) UGoapAction* CurrentAction;
	UPROPERTY(EditAnywhere) FWMWorldStates CurrentWorldState;

	//TMap<FSubGoal, int> Goals;
	TArray<FSubGoalImportance> Goals;
	UPROPERTY(EditAnywhere) USubGoal* CurrentGoal;
	
	UPROPERTY(EditAnywhere) TArray<UGoapAction*> Actions = TArray<UGoapAction*>();
	//UPROPERTY(EditAnywhere) AGameStateSinWM* WorldState = nullptr;

	int DebugCounter = 0;
}; 
