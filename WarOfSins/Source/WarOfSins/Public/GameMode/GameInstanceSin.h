// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceSin.generated.h"

class UClassInfoDataAsset;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UGameInstanceSin : public UGameInstance
{
	GENERATED_BODY()


public:
	UClassInfoDataAsset* GetClassInfoDataAsset();

	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UClassInfoDataAsset* ClassInfoDataAsset;
};
