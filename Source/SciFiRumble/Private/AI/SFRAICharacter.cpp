// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SFRAICharacter.h"

ASFRAICharacter::ASFRAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

FBarrelRotation ASFRAICharacter::GetBarrelRotation()
{
	if (IsValid(AimTarget) && !AimTarget->IsPendingKill())
	{
		return AimTarget->GetActorLocation();
	}
	return FVector::ZeroVector;
}
