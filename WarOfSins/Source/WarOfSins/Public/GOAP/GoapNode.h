// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoapNode.generated.h"

class UGoapAction;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable)
class WAROFSINS_API UGoapNode : public UObject
{
	GENERATED_BODY()
public:
	UGoapNode();

	void Init(UGoapNode* NewParent, float NewRunningCost, TMap<FString, int> NewState, UGoapAction* NewAction);

	/* Getters */
	UGoapNode* GetParent();
	float GetRunningCost();
	TMap<FString, int> GetState();
	UGoapAction* GetAction();

	/* Setters */
	void SetParent(UGoapNode* NewParent);
	void SetRunningCost(float NewRunningCost);
	void SetState(TMap<FString, int> NewState);
	void SetAction(UGoapAction* NewAction);
	
protected:
	UPROPERTY(EditAnywhere) UGoapNode* Parent;
	UPROPERTY(EditAnywhere) float RunningCost;
	UPROPERTY(EditAnywhere) TMap<FString, int> State;
	UPROPERTY(EditAnywhere) UGoapAction* Action;
};
