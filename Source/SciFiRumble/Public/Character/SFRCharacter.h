// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SFRDestroyZoneInterface.h"
#include "SFRCharacter.generated.h"


class ASFRBulletProjectileActor;
UENUM(BlueprintType)
enum class ERotationMethod : uint8
{
	NotImplemented,
	Rotation,
	LookAt,
};

USTRUCT(BlueprintType)
struct FBarrelRotation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float Rotation;

	UPROPERTY(BlueprintReadWrite)
	FVector LookAt;
	
	UPROPERTY(BlueprintReadWrite)
	ERotationMethod RotationMethod;

	FBarrelRotation() : Rotation(0.0f), LookAt(FVector::ZeroVector), RotationMethod(ERotationMethod::NotImplemented)
	{}
	
	FBarrelRotation(const ERotationMethod RotationMethod) : Rotation(0.0f), LookAt(FVector::ZeroVector), RotationMethod(RotationMethod)
	{}

	FBarrelRotation(const FVector LookAt) : Rotation(0.0f), LookAt(LookAt), RotationMethod(ERotationMethod::LookAt)
	{}

	FBarrelRotation(const float Rotation) : Rotation(Rotation), LookAt(FVector::ZeroVector), RotationMethod(ERotationMethod::Rotation)
	{}
};

UCLASS()
class SCIFIRUMBLE_API ASFRCharacter : public ACharacter, public ISFRDestroyZoneInterface
{
	GENERATED_BODY()

protected:
	uint8 Ammo;

	// 1 = no resistance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1.0", UIMin = "1.0"))
	float LaunchResist = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ASFRBulletProjectileActor> BulletClass;

	// for get rotation to shoot the bullet
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BarrelSocketName = FName("Barrel");

	// ProjectileVelocity = ShootVelocityMultiplier * Ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ShootVelocityMultiplier = 1000;

public:

	ASFRCharacter();

	void ChangeAmmo(const int Value);

	void EmptyAmmo() {ChangeAmmo(Ammo * -1);}

	UFUNCTION(BlueprintNativeEvent)
	void OnAmmoChange(uint8 NewAmmo, int ChangeAmount);
    
	uint8 GetAmmo() const {return Ammo;}

	float GetLaunchResistance () const {return LaunchResist;}

	void Fire();

	UFUNCTION(BlueprintCallable)
	virtual FBarrelRotation GetBarrelRotation();

	virtual bool CustomDestroy_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
	bool OnCustomDestroy();
	
protected:

	virtual void BeginPlay() override;

};
