// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFRSplineProjectileActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USplineComponent;
class UTimelineComponent;
UCLASS()
class SCIFIRUMBLE_API ASFRSplineProjectileActor : public AActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USplineComponent* Spline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* TriggerSphere;
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Direction of the projectile launch
	UPROPERTY(EditInstanceOnly, meta=(MakeEditWidget))
	FVector LaunchTarget;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float Velocity;

	// Can Scale the predict
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int PredictRange = 2;
	
	// Delay from begin play to projectile launch in sec
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float LaunchTimeDelay = 5;
	
public:	
	ASFRSplineProjectileActor();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	
	UFUNCTION()
	void FireTheProjectile();

	UFUNCTION(BlueprintNativeEvent)
	void OnProjectileFire();

	UFUNCTION()
	void GameStart();
};
