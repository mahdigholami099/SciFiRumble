// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/SFRMultiplayerGameMode.h"
#include "UObject/NoExportTypes.h"
#include "SFRCharacterVariety.generated.h"

class ASFRCharacter;
class USFRSkinVariety;
/**
 * 
 */
UCLASS(Blueprintable)
class SCIFIRUMBLE_API USFRCharacterVariety : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TSubclassOf<USFRSkinVariety>> SkinVariety;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly)
	bool ReinitPoseOnSetCharacter = true;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCharacter(ASFRCharacter* CharacterActorRef);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSkin(ASFRCharacter* CharacterActorRef, int SkinIndex);
};
