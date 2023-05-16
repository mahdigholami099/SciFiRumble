// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SFRMultiplayerGameState.generated.h"

class ASFRCameraActor;
/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRMultiplayerGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ASFRCameraActor* Camera;

public:

	UFUNCTION(BlueprintCallable)
	ASFRCameraActor* GetCamera() const {return Camera;}
	
protected:

	virtual void BeginPlay() override;
};
