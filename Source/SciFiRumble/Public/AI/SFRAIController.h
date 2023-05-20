// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SFRAIController.generated.h"


USTRUCT(BlueprintType)
struct FRange
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Min;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Max;

	FRange(): Min(0.0f), Max(1.0f)
	{}

	FRange(const float Min, const float Max): Min(Min), Max(Max)
	{}
};


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RandomMoveRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MoveThreadRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShootThreadRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRange ShootThreadRandomDelay = {1.0f, 5.0f};
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveThread();

	UFUNCTION()
	void ShootThread();

	UFUNCTION()
	void GameStart();
	
};
