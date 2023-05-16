// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/SFRCameraActor.h"

#include "Kismet/GameplayStatics.h"

void ASFRCameraActor::Shake() const
{
	if (IsValid(ShakeClass))
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), ShakeClass, GetActorLocation(), 0.0f, 500.0f);
	}
}
