// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameSettingsDataAsset.generated.h"

class UClassInfoDataAsset;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UGameSettingsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/* Others DA */
	UPROPERTY(EditAnywhere, Category="Data Assets") UClassInfoDataAsset* ClassInfoDataAsset;
	
};
