// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClassInfoDataAsset.generated.h"

class ABuilding;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UClassInfoDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TSubclassOf<ABuilding> BuildingClass;
};
