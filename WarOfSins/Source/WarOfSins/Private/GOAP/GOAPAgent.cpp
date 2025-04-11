// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/GOAPAgent.h"

#include "GOAP/Planner.h"
#include "GOAP/SubGoal.h"

// Sets default values
AGOAPAgent::AGOAPAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGOAPAgent::BeginPlay()
{
	Super::BeginPlay();
	//WorldState = GetWorld()->GetGameState<AGameStateSinWM>();
	// fill actions
	
}

void AGOAPAgent::GoapTick(float DeltaTime)
{
	if (DebugCounter > 5) return;
	
	if (Goals.Num() == 0)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "No goals");
		// UE_LOG(LogTemp, Warning, TEXT("No goals"));
		return;
	}
	
	if (CurrentAction && CurrentAction->IsRunning())
	{
		// finish stuff
		auto CouldContinue = CurrentAction->Progress(DeltaTime, this);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Action progress: %s"), *CurrentAction->GetActionName()));

		if (!CouldContinue)
		{
			/* Will replan next tick */
			Planner = nullptr;
			Plan.Empty();
			CurrentAction = nullptr;
			return;
		}

		if (CurrentAction->IsFinished())
		{
			CurrentAction->PostPerformAction(this);
			GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Green, FString::Printf(TEXT("Action finished: %s"), *CurrentAction->GetActionName()));
			UE_LOG(LogTemp, Warning, TEXT("Action finished: %s"), *CurrentAction->GetActionName());
			for (auto Effect : CurrentAction->GetEffects())
			{
				CurrentWorldState.ModifyState(Effect.Key, Effect.Value);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("\tEffect applied: %s, %d"), *Effect.Key, Effect.Value));
				UE_LOG(LogTemp, Warning, TEXT("\tEffect applied: %s, %d"), *Effect.Key, Effect.Value);
			}
			CurrentAction = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("\tPlan size: %d"), Plan.Num());


			/* Check if we have finished our goal */
			if (Plan.IsEmpty() && CurrentGoal)
			{
				if (CurrentGoal->bRemove)
				{
					RemoveGoalFromGoals(CurrentGoal);
				}
				Planner = nullptr;
				CurrentGoal = nullptr;
			}
			
		}
		return;
	}

	
	if (Planner == nullptr || Plan.IsEmpty())
	{
		Planner = NewObject<UPlanner>();

		/* sort goals by importance from highest to lowest */
		Goals.Sort([](const FSubGoalImportance& A, const FSubGoalImportance& B) { return A.Importance > B.Importance; });

		int ActionsAvailable = Actions.Num();
		if (ActionsAvailable == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No actions available"));
			return;
		}

		for (auto Goal : Goals)
		{
			UE_LOG(LogTemp, Warning, TEXT("Trying to plan for %d goals"), Goal.SubGoal->SubGoals.Num());
			Plan = Planner->Plan(CurrentWorldState.GetStates(), Goal.SubGoal->SubGoals, Actions);
			DebugCounter++;
			if (Plan.Num() > 0)
			{
				CurrentGoal = Goal.SubGoal;
				UE_LOG(LogTemp, Warning, TEXT("Plan found with %d actions"), Plan.Num());
				for (auto Action : Plan)
				{
					UE_LOG(LogTemp, Warning, TEXT("\tAction: %s"), *Action->GetActionName());
				}
				break;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Plan not found!"));
			}
		}
	}

	if (!Plan.IsEmpty())
	{
		CurrentAction = Plan[0];
		UE_LOG(LogTemp, Warning, TEXT("Doing action, before plan size %d"), Plan.Num());
		if (CurrentAction->IsAchievable(CurrentWorldState.GetStates()))
		{
			CurrentAction->PrePerformAction(this);
			Plan.RemoveAt(0);
			UE_LOG(LogTemp, Warning, TEXT("\tAfter plan size %d"), Plan.Num());
		}
		else
		{
			// replan
			Planner = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Replanning since action was not achievable (%s)"), *CurrentAction->GetActionName());
			Plan.Empty();
		}
	}
}

void AGOAPAgent::RemoveGoalFromGoals(const USubGoal* Goal)
{
	UE_LOG(LogTemp, Warning, TEXT("Removing goal..."));
	bool removed = false;
	for (int i = 0; i < Goals.Num(); i++)
	{
		if (Goals[i].SubGoal == Goal)
		{
			Goals.RemoveAt(i);
			UE_LOG(LogTemp, Warning, TEXT("Removed goal!"));
			removed = true;
			break;
		}
	}
	if (!removed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to remove goal"));
	}
	
}

// Called every frame
void AGOAPAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GoapTick(DeltaTime);
}

// Called to bind functionality to input
void AGOAPAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

