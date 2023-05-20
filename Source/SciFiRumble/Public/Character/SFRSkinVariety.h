// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SFRSkinVariety.generated.h"

UENUM(BlueprintType)
enum class ESetMaterialType : uint8
{
	Loop,
	Exact
};

USTRUCT(BlueprintType)
struct FLoopRange
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int From;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int To;
};

USTRUCT(BlueprintType)
struct FSkinMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* Material;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESetMaterialType SetMaterialType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="SetMaterialType == ESetMaterialType::Loop", EditConditionHides))
	FLoopRange LoopRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="SetMaterialType == ESetMaterialType::Exact", EditConditionHides))
	TArray<int> Indexes;
};

USTRUCT(BlueprintType)
struct FEmissiveIndex
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESetMaterialType SetMaterialType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="SetMaterialType == ESetMaterialType::Loop", EditConditionHides))
	FLoopRange LoopRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="SetMaterialType == ESetMaterialType::Exact", EditConditionHides))
	TArray<int> Indexes;
};

class ASFRCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class SCIFIRUMBLE_API USFRSkinVariety : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSkinMaterial> SkinMaterials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FEmissiveIndex EmissiveChanger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName EmissiveParameterName = FName("EmissiveMultiplier");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EmissiveMultiplier = 10.0f;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetSkin(ASFRCharacter* CharacterActorRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChangeEmissive(ASFRCharacter* CharacterActorRef, const float Value);
	
};
