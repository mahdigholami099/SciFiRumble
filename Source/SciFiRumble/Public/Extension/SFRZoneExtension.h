// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "SFRZoneExtension.generated.h"

class ASFRMultiplayerGameState;
/**
 * 
 */
UCLASS(MinimalAPI, Blueprintable, BlueprintType)
class USFRZoneExtension : public UObject
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintNativeEvent)
	void Init(ASFRMultiplayerGameState* GameState, FVector OtherActorLocation);

	virtual void CppInit(ASFRMultiplayerGameState* GameState, FVector OtherActorLocation);
};
