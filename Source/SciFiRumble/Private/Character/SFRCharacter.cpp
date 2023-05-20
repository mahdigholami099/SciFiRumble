// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRCharacter.h"

#include "Character/SFRCharacterVariety.h"
#include "Character/SFRSkinVariety.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/SFRBulletProjectileActor.h"


ASFRCharacter::ASFRCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASFRCharacter::ChangeAmmo(const int Value)
{
	Ammo += Value;
	OnAmmoChange(Ammo, Value);
}

void ASFRCharacter::OnAmmoChange_Implementation(uint8 NewAmmo, int ChangeAmount)
{
	if (!CharacterVariety.IsValidIndex(CharacterIndex)) return;
	USFRCharacterVariety* MyCharacter = CharacterVariety[CharacterIndex].GetDefaultObject();
	if (!MyCharacter->SkinVariety.IsValidIndex(SkinIndex)) return;
	USFRSkinVariety* MySkin = MyCharacter->SkinVariety[SkinIndex].GetDefaultObject();
	MySkin->ChangeEmissive(this, NewAmmo);
}

void ASFRCharacter::Fire()
{
	if (Ammo <= 0) return;
	FTransform Transform;
	Transform.SetLocation(GetMesh()->GetSocketLocation(BarrelSocketName));
	ASFRBulletProjectileActor* Bullet = GetWorld()->SpawnActorDeferred<ASFRBulletProjectileActor>(BulletClass, Transform, this);
	Bullet->Velocity = UKismetMathLibrary::GetRightVector(GetMesh()->GetSocketRotation(BarrelSocketName)) * (Ammo * ShootVelocityMultiplier);
	Bullet->FinishSpawning(Transform);
	EmptyAmmo();
}

FBarrelRotation ASFRCharacter::GetBarrelRotation()
{
	return ERotationMethod::NotImplemented;
}

bool ASFRCharacter::CustomDestroy_Implementation()
{
	return OnCustomDestroy();
}

void ASFRCharacter::ChangeCharacter_Implementation(EOrder Order)
{
	const int Len = CharacterVariety.Num();
	if (Len == 0) return;
	SkinIndex = 0;

	if (Order == EOrder::Next)
	{
		CharacterIndex++;
		if (CharacterIndex >= Len) CharacterIndex = 0;
	}
	else
	{
		CharacterIndex--;
		if (CharacterIndex < 0) CharacterIndex = Len -1;
	}
	

	CharacterVariety[CharacterIndex].GetDefaultObject()->SetCharacter(this);
	CharacterVariety[CharacterIndex].GetDefaultObject()->SetSkin(this, SkinIndex);
}

bool ASFRCharacter::OnCustomDestroy_Implementation()
{
	return true;
}

void ASFRCharacter::ChangeSkin_Implementation(EOrder Order)
{
	if (!CharacterVariety.IsValidIndex(CharacterIndex)) return;
	const int Len = CharacterVariety[CharacterIndex].GetDefaultObject()->SkinVariety.Num();
	if (Len == 0) return;

	if (Order == EOrder::Next)
	{
		SkinIndex++;
		if (SkinIndex >= Len) SkinIndex = 0;
	}
	else
	{
		SkinIndex--;
		if (SkinIndex < 0) SkinIndex = Len -1;
	}

	CharacterVariety[CharacterIndex].GetDefaultObject()->SetSkin(this, SkinIndex);
}

void ASFRCharacter::BeginPlay()
{
	Super::BeginPlay();

	ChangeCharacter(EOrder::Next);
}


