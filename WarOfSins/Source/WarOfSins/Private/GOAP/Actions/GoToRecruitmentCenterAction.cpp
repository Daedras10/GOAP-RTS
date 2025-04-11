// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/Actions/GoToRecruitmentCenterAction.h"

#include "DataAssets/ClassInfoDataAsset.h"
#include "FunctionLibrary/BlueprintFunctionLibrarySin.h"
#include "GOAP/GOAPAgent.h"
#include "Kismet/GameplayStatics.h"
#include "LD/Buildings/Building.h"

UGoToRecruitmentCenterAction::UGoToRecruitmentCenterAction()
{
	ActionName = "GoToRecruitmentCenter";
	Cost = 0;

	Effects.Add("AtRecruitmentCenter", 1);
}

bool UGoToRecruitmentCenterAction::PrePerformAction(AGOAPAgent* GoapAgent)
{
	Super::PrePerformAction(GoapAgent);

	/* Find a recruitment building */
	//TODO closest?
	TArray<AActor*> FoundActors;
	auto ClassInfo = UBlueprintFunctionLibrarySin::GetClassInfoDataAsset(GoapAgent);
	TSubclassOf<ABuilding> BuildingClass = ClassInfo->BuildingClass;
	UGameplayStatics::GetAllActorsOfClass(GoapAgent->GetWorld(), BuildingClass, FoundActors);
	for (AActor* Actor : FoundActors)
	{
		ABuilding* Building = Cast<ABuilding>(Actor);
		if (Building)
		{
			RecruitmentBuilding = Building;
			break;
		}
	}

	return RecruitmentBuilding != nullptr;
}

bool UGoToRecruitmentCenterAction::PostPerformAction(AGOAPAgent* GoapAgent)
{
	RecruitmentBuilding = nullptr;
	return Super::PostPerformAction(GoapAgent);
}

bool UGoToRecruitmentCenterAction::Progress(float DeltaTime, AGOAPAgent* GoapAgent)
{
	if (State == EGOAPState::GOAPState_Finished) return true;
	if (RecruitmentBuilding == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "No recruitment building found");
		return false;
	}

	bool CanContinue = true; // TODO
	auto AgentLocation = GoapAgent->GetActorLocation();
	auto BuildingLocation = RecruitmentBuilding->GetActorLocation();

	/* Check if we're not already close enough */
	auto Distance = FVector::Dist(AgentLocation, BuildingLocation);
	if (Distance < 200.0f)
	{
		State = EGOAPState::GOAPState_Finished;
		return CanContinue;
	}

	auto NewLocation = FMath::Lerp(AgentLocation, BuildingLocation, DeltaTime*0.5f);
	GoapAgent->SetActorLocation(NewLocation);

	Distance = FVector::Dist(NewLocation, BuildingLocation);
	if (Distance < 200.0f)
	{
		State = EGOAPState::GOAPState_Finished;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Distance: %f"), Distance));
	}

	return CanContinue;
}
