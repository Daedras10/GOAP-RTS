// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"

USTRUCT(Blueprintable)
struct FWMWorldState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Key;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Value;
};


/* TODO? Should be a class */
USTRUCT(Blueprintable)
struct FWMWorldStates
{
	GENERATED_BODY()

public:
	bool HasState(FString Key);
	void AddState(FString Key, int Value);
	void SetState(FString Key, int Value);
	void ModifyState(FString Key, int ValueToAdd);
	void RemoveState(FString Key);
	TMap<FString, int> GetStates();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, int> WorldStates = TMap<FString, int>();
};
