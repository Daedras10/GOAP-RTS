// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAP/Actions/GoapAction.h"
#include "RecruitAction.generated.h"

/**
 * 
 */
UCLASS()
class WAROFSINS_API URecruitAction : public UGoapAction
{
	GENERATED_BODY()
public:
	URecruitAction();
	
	virtual bool PrePerformAction(AGOAPAgent* GoapAgent) override;
	virtual bool PostPerformAction(AGOAPAgent* GoapAgent) override;
	virtual bool Progress(float DeltaTime, AGOAPAgent* GoapAgent) override;

protected:
	UPROPERTY(EditAnywhere) float RecruitmentTime = 2.0f;
	UPROPERTY(EditAnywhere) float RecruitmentTimer = 0.0f;
};
