// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRSkinVariety.h"

#include "Character/SFRCharacter.h"

void USFRSkinVariety::SetSkin_Implementation(ASFRCharacter* CharacterActorRef)
{
	for (FSkinMaterial& SkinMaterial: SkinMaterials)
	{
		if (SkinMaterial.SetMaterialType == ESetMaterialType::Exact)
		{
			for (const int Index: SkinMaterial.Indexes)
			{
				CharacterActorRef->GetMesh()->SetMaterial(Index, SkinMaterial.Material);
			}
		}
		else
		{
			for (int Index = SkinMaterial.LoopRange.From; Index <= SkinMaterial.LoopRange.To; ++Index)
			{
				CharacterActorRef->GetMesh()->SetMaterial(Index, SkinMaterial.Material);
			}
		}
	}
}
