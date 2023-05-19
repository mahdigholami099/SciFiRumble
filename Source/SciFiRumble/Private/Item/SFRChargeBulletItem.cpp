// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SFRChargeBulletItem.h"

#include "Character/SFRCharacter.h"
#include "Components/BoxComponent.h"

ASFRChargeBulletItem::ASFRChargeBulletItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(Root);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	TriggerBox->SetupAttachment(Root);

}

void ASFRChargeBulletItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASFRCharacter* Character = Cast<ASFRCharacter>(OtherActor))
	{
		Character->ChangeAmmo(1);
		Destroy();
	}
}

// Called when the game starts or when spawned
void ASFRChargeBulletItem::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASFRChargeBulletItem::BeginOverlap);

}


