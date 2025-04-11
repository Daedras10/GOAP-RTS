// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/GoapNode.h"


UGoapNode::UGoapNode()
{
}

void UGoapNode::Init(UGoapNode* NewParent, float NewRunningCost, TMap<FString, int> NewState, UGoapAction* NewAction)
{
	this->Parent = NewParent;
	this->RunningCost = NewRunningCost;
	this->State = TMap(NewState);
	this->Action = NewAction;
}

UGoapNode* UGoapNode::GetParent()
{
	return Parent;
}

float UGoapNode::GetRunningCost()
{
	return RunningCost;
}

TMap<FString, int> UGoapNode::GetState()
{
	return State;
}

UGoapAction* UGoapNode::GetAction()
{
	return Action;
}

void UGoapNode::SetParent(UGoapNode* NewParent)
{
	this->Parent = NewParent;
}

void UGoapNode::SetRunningCost(float NewRunningCost)
{
	this->RunningCost = NewRunningCost;
}

void UGoapNode::SetState(TMap<FString, int> NewState)
{
	this->State = TMap(NewState);
}

void UGoapNode::SetAction(UGoapAction* NewAction)
{
	this->Action = NewAction;
}
