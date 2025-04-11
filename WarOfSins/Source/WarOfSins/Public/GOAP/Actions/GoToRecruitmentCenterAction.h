// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/Actions/GoapAction.h"
#include "GoToRecruitmentCenterAction.generated.h"

class ABuilding;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UGoToRecruitmentCenterAction : public UGoapAction
{
	GENERATED_BODY()

public:
	UGoToRecruitmentCenterAction();

	virtual bool PrePerformAction(AGOAPAgent* GoapAgent) override;
	virtual bool PostPerformAction(AGOAPAgent* GoapAgent) override;
	virtual bool Progress(float DeltaTime, AGOAPAgent* GoapAgent) override;
	
protected:
	ABuilding* RecruitmentBuilding;
};
