// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SFRBulletProjectileActor.h"

#include "Character/SFRCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASFRBulletProjectileActor::ASFRBulletProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	ProjectileMesh->SetupAttachment(Root);
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(FName("TriggerBox"));
	TriggerSphere->SetupAttachment(Root);
	
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ASFRBulletProjectileActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() != OtherActor)
	{
		if (ASFRCharacter* Character = Cast<ASFRCharacter>(OtherActor))
		{
			Character->LaunchCharacter(Velocity / Character->GetLaunchResistance(), false, false);
			OnHit(OtherActor);
			Destroy();
		}
	}
}

void ASFRBulletProjectileActor::OnHit_Implementation(AActor* OtherActor)
{
}

void ASFRBulletProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ASFRBulletProjectileActor::BeginOverlap);

	ProjectileMovementComponent->Velocity = Velocity;
}

