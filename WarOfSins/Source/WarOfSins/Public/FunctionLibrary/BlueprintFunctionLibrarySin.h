// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctionLibrarySin.generated.h"

class UGameSettingsDataAsset;
class UClassInfoDataAsset;
class UGameInstanceSin;
/**
 * 
 */
UCLASS()
class WAROFSINS_API UBlueprintFunctionLibrarySin : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UGameInstanceSin* GetGameInstanceSin(UObject* WorldContextObject);
	static UClassInfoDataAsset* GetClassInfoDataAsset(UObject* WorldContextObject);
	static UGameSettingsDataAsset* GetGameSettingsDataAsset(UObject* WorldContextObject);
};
