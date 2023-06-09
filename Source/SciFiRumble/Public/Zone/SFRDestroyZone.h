// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFRDestroyZone.generated.h"

class UBoxComponent;
UCLASS()
class SCIFIRUMBLE_API ASFRDestroyZone : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* TriggerBox;
	
public:
	
	ASFRDestroyZone();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginDestroy(AActor* OtherActor);

protected:

	virtual void BeginPlay() override;

};
