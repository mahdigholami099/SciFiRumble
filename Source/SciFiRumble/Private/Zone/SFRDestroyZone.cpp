// Fill out your copyright notice in the Description page of Project Settings.


#include "Zone/SFRDestroyZone.h"

#include "Components/BoxComponent.h"
#include "Extension/SFRZoneExtension.h"
#include "GameState/SFRMultiplayerGameState.h"
#include "Interface/SFRDestroyZoneInterface.h"

ASFRDestroyZone::ASFRDestroyZone()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
}

void ASFRDestroyZone::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASFRDestroyZone::BeginOverlap);
}

void ASFRDestroyZone::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(USFRDestroyZoneInterface::StaticClass()))
	{
		bool bIsDestroyed = false;
		if (ISFRDestroyZoneInterface* Interface = Cast<ISFRDestroyZoneInterface>(OtherActor))
		{
			bIsDestroyed = Interface->CustomDestroy_Implementation();
		}
		else
		{
			bIsDestroyed = ISFRDestroyZoneInterface::Execute_CustomDestroy(this);
		}
		if (bIsDestroyed)
		{
			for (TSubclassOf<USFRZoneExtension>& AfterDestroyEffect: AfterDestroyEffects)
			{
				USFRZoneExtension* Effect = AfterDestroyEffect.GetDefaultObject();
				Effect->Init(GetWorld()->GetGameState<ASFRMultiplayerGameState>(), OtherActor->GetActorLocation());
			}
		}
	}
}