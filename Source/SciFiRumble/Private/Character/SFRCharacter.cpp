// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRCharacter.h"

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

bool ASFRCharacter::OnCustomDestroy_Implementation()
{
	return true;
}

void ASFRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


