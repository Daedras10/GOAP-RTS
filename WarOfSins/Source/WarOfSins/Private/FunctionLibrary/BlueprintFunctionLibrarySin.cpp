// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/BlueprintFunctionLibrarySin.h"

#include "GameMode/GameInstanceSin.h"
#include "Kismet/GameplayStatics.h"

UGameInstanceSin* UBlueprintFunctionLibrarySin::GetGameInstanceSin(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is null"));
		return nullptr;
	}
	auto WorldContext = WorldContextObject->GetWorld();
	if (!WorldContext)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContext v2 is null"));
		return nullptr;
	}
	auto GameInstance = UGameplayStatics::GetGameInstance(WorldContext);
	if (!GameInstance) UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));
	auto GameInstanceSin = Cast<UGameInstanceSin>(GameInstance);
	if (!GameInstanceSin) UE_LOG(LogTemp, Error, TEXT("GameInstanceSin is null"));
	return GameInstanceSin;
}

UClassInfoDataAsset* UBlueprintFunctionLibrarySin::GetClassInfoDataAsset(UObject* WorldContextObject)
{
	auto GameInstanceSin = GetGameInstanceSin(WorldContextObject);
	if (!GameInstanceSin) return nullptr;
	return GameInstanceSin->GetClassInfoDataAsset();
}

UGameSettingsDataAsset* UBlueprintFunctionLibrarySin::GetGameSettingsDataAsset(UObject* WorldContextObject)
{
	auto GameInstanceSin = GetGameInstanceSin(WorldContextObject);
	if (!GameInstanceSin) return nullptr;
	return GameInstanceSin->GetGameSettingsDataAsset();
}
