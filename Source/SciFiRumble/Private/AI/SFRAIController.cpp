// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SFRAIController.h"

#include "NavigationSystem.h"
#include "AI/SFRAICharacter.h"
#include "Character/SFRCharacter.h"
#include "GameFramework/Character.h"
#include "Item/SFRChargeBulletItem.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/SFRSplineProjectileActor.h"

void ASFRAIController::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeNotCasted = UGameplayStatics::GetGameMode(GetWorld());
	if (!IsValid(GameModeNotCasted)) return;

	if (ASFRMultiplayerGameMode* GameMode = Cast<ASFRMultiplayerGameMode>(GameModeNotCasted))
	{
		GameMode->OnGameStart.AddDynamic(this, &ASFRAIController::GameStart);
	}
}

void ASFRAIController::MoveThread()
{
	// if ai going to somewhere avoid interruption
	if (GetMoveStatus() == EPathFollowingStatus::Moving) return;
	
	// pause timer for avoid interruption
	if (MoveThreadTimerHandle.IsValid())
	{
		GetWorldTimerManager().PauseTimer(MoveThreadTimerHandle);
	}


	// get all Chargers
	TArray<AActor*> Chargers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFRChargeBulletItem::StaticClass(), Chargers);

	// we found some chargers so lets go catch them :)
	if (Chargers.Num() > 0)
	{
		// sort chargers by distance from closest to farthest 
		FVector MyLocation = GetCharacter()->GetActorLocation();
		auto SortByDistance = [MyLocation](const AActor& A, const AActor& B)
		{
			const float DistanceToA = FVector::Distance(MyLocation, A.GetActorLocation());
			const float DistanceToB = FVector::Distance(MyLocation, B.GetActorLocation());
			return DistanceToA < DistanceToB;
		};
		Chargers.Sort(SortByDistance);

		TArray<AActor*> Characters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFRCharacter::StaticClass(), Characters);
		Characters.RemoveAt(Characters.Find(GetCharacter()));
		
		for (AActor* Charger: Chargers)
		{
			bool bReachable = true;
			for (const AActor* OtherCharacter: Characters)
			{
				if (FVector::Distance(MyLocation, Charger->GetActorLocation()) > FVector::Distance(OtherCharacter->GetActorLocation(), Charger->GetActorLocation()))
				{
					bReachable = false;
					break;
				}
			}
			if (bReachable)
			{
				MoveToActor(Charger, 10.f);
				break;
			}
		}
		
	}
	// we should move just randomly cause no charger found
	if (GetMoveStatus() != EPathFollowingStatus::Moving)
	{
		UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
		FNavLocation NavLocationResult;
		if (NavArea->GetRandomReachablePointInRadius(GetCharacter()->GetActorLocation(), RandomMoveRange, NavLocationResult))
		{
			MoveToLocation(NavLocationResult.Location, 10.f);
		}
	}

	// start timer to continue its job
	if (MoveThreadTimerHandle.IsValid())
	{
		GetWorldTimerManager().UnPauseTimer(MoveThreadTimerHandle);
	}
}

void ASFRAIController::ShootThread()
{
	// pause timer for avoid interruption
	if (ShootThreadTimerHandle.IsValid())
	{
		GetWorldTimerManager().PauseTimer(ShootThreadTimerHandle);
	}

	// get all character and remove self from array
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFRCharacter::StaticClass(), Characters);
	Characters.RemoveAt(Characters.Find(GetCharacter()));

	ASFRAICharacter* MyCharacter = Cast<ASFRAICharacter>(GetCharacter());
	if (Characters.Num() > 0)
	{
		MyCharacter->AimTarget = Characters[FMath::RandRange(0, Characters.Num() - 1)];
	}

	const int Ammo = MyCharacter->GetAmmo();
	const float RandomValue = FMath::FRand();

	if (RandomValue <= Ammo * 0.2f)
	{
		if (IsValid(MyCharacter->AimTarget))
		{
			MyCharacter->Fire();
		}
	}


	FTimerHandle DelayHandle;
	const float DelaySeconds = FMath::RandRange(ShootThreadRandomDelay.Min, ShootThreadRandomDelay.Max);
	GetWorldTimerManager().SetTimer(DelayHandle, [=]
	{
		// start timer to continue its job
		if (ShootThreadTimerHandle.IsValid())
		{
			GetWorldTimerManager().UnPauseTimer(ShootThreadTimerHandle);
		}
	}, DelaySeconds, false);
}

void ASFRAIController::GameStart()
{
	GetWorldTimerManager().SetTimer(MoveThreadTimerHandle, this, &ASFRAIController::MoveThread, MoveThreadRate, true);
	GetWorldTimerManager().SetTimer(ShootThreadTimerHandle, this, &ASFRAIController::ShootThread, ShootThreadRate, true);
}
