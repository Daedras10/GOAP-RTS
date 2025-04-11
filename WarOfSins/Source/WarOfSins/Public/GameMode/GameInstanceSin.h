// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceSin.generated.h"

class UGameSettingsDataAsset;
class UClassInfoDataAsset;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UGameInstanceSin : public UGameInstance
{
	GENERATED_BODY()


public:
	UClassInfoDataAsset* GetClassInfoDataAsset(); /* Could be removed since we can access it from GameSettings */
	UGameSettingsDataAsset* GetGameSettingsDataAsset();

	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UGameSettingsDataAsset* GameSettingsDataAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UClassInfoDataAsset* ClassInfoDataAsset;
};
