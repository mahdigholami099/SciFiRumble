// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SFRCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRCameraActor : public ACameraActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> ShakeClass;

public:
	UFUNCTION(BlueprintCallable)
	void Shake() const;
	
};
