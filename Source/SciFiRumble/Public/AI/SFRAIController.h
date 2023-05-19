// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SFRAIController.generated.h"

class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRAIController : public AAIController
{
	GENERATED_BODY()

protected:

	FTimerHandle MoveThreadTimerHandle;
	
	FTimerHandle ShootThreadTimerHandle;

	UPROPERTY()
	UNavigationSystemV1* NavArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RandomMoveRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MoveThreadRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShootThreadRate = 0.5f;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveThread();

	UFUNCTION()
	void ShootThread();
	
};
