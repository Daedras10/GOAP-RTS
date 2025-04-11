// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateSinWM.generated.h"

struct FWMWorldStates;
/**
 * 
 */
UCLASS()
class WAROFSINS_API AGameStateSinWM : public AGameStateBase
{
	GENERATED_BODY()
public:
	AGameStateSinWM();

	FWMWorldStates* GetWorldStates();

public:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FWMWorldStates* WorldStates;
};
