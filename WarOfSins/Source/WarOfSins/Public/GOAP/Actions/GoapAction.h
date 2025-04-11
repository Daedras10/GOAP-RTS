// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Enums.h"
#include "GoapAction.generated.h"

class AGOAPAgent;
enum class EGOAPState : uint8;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable)
class WAROFSINS_API UGoapAction : public UObject
{
	GENERATED_BODY()
public:
	UGoapAction();

	bool IsAchievable(TMap<FString, int> WorldStates);
	bool IsRunning();
	bool IsFinished();

	virtual bool PrePerformAction(AGOAPAgent* GoapAgent);
	virtual bool PostPerformAction(AGOAPAgent* GoapAgent);
	virtual bool Progress(float DeltaTime, AGOAPAgent* GoapAgent);

	FString GetActionName();
	int GetCost();
	TMap<FString, int> GetPreconditions();
	TMap<FString, int> GetEffects();

	// TArray<FWMWorldState> GetPreconditionsStruct();
	// TArray<FWMWorldState> GetEffectsStruct();


protected:
	UPROPERTY(EditAnywhere) FString ActionName = "Action";
	UPROPERTY(EditAnywhere) int Cost = 1.0f;

	/* Will see if we use theses, in editor likely since we can't see TMap in editor */
	// UPROPERTY(EditAnywhere) TArray<FWMWorldState> PreconditionsStruct = TArray<FWMWorldState>();
	// UPROPERTY(EditAnywhere) TArray<FWMWorldState> EffectsStruct = TArray<FWMWorldState>();

	UPROPERTY(EditAnywhere) TMap<FString, int> Preconditions = TMap<FString, int>();
	UPROPERTY(EditAnywhere) TMap<FString, int> Effects = TMap<FString, int>();

	UPROPERTY(EditAnywhere) EGOAPState State = EGOAPState::GOAPState_NotStarted;
};
