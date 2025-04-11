// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/GOAPAgent.h"
#include "TroopGatherer.generated.h"

class ABuilding;
/**
 * 
 */
UCLASS()
class WAROFSINS_API ATroopGatherer : public AGOAPAgent
{
	GENERATED_BODY()

public:
	ATroopGatherer();

	void AddTroops(int TroopToAdd);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int GathererCount = 0;
};
