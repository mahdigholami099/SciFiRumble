// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRCharacterVariety.h"

#include "Character/SFRCharacter.h"
#include "Character/SFRSkinVariety.h"

void USFRCharacterVariety::SetCharacter_Implementation(ASFRCharacter* CharacterActorRef)
{
	CharacterActorRef->GetMesh()->SetSkeletalMesh(SkeletalMesh, ReinitPoseOnSetCharacter);
}

void USFRCharacterVariety::SetSkin_Implementation(ASFRCharacter* CharacterActorRef, int SkinIndex)
{
	SkinVariety[SkinIndex].GetDefaultObject()->SetSkin(CharacterActorRef);
}
