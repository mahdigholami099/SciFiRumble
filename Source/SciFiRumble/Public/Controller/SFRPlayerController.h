// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SFRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
