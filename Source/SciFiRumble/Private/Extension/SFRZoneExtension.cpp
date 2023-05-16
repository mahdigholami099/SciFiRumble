// Fill out your copyright notice in the Description page of Project Settings.


#include "Extension/SFRZoneExtension.h"

#include "GameState/SFRMultiplayerGameState.h"

USFRZoneExtension::USFRZoneExtension(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USFRZoneExtension::Init_Implementation(ASFRMultiplayerGameState* GameState, FVector OtherActorLocation)
{
	CppInit(GameState, OtherActorLocation);
}

void USFRZoneExtension::CppInit(ASFRMultiplayerGameState* GameState, FVector OtherActorLocation)
{
}
