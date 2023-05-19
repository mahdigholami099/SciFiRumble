// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SFRAIController.h"

#include "NavigationSystem.h"
#include "Character/SFRCharacter.h"
#include "GameFramework/Character.h"
#include "Item/SFRChargeBulletItem.h"
#include "Kismet/GameplayStatics.h"

void ASFRAIController::BeginPlay()
{
	Super::BeginPlay();

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	GetWorldTimerManager().SetTimer(MoveThreadTimerHandle, this, &ASFRAIController::MoveThread, MoveThreadRate, true);
	GetWorldTimerManager().SetTimer(ShootThreadTimerHandle, this, &ASFRAIController::ShootThread, ShootThreadRate, true);
}

void ASFRAIController::MoveThread()
{
	// if ai going to somewhere avoid interruption
	if (GetMoveStatus() == EPathFollowingStatus::Moving) return;
	
	// pause timer for avoid interruption
	GetWorldTimerManager().PauseTimer(MoveThreadTimerHandle);


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
				MoveToActor(Charger);
				break;
			}
		}
		
	}
	// we should move just randomly cause no charger found
	if (GetMoveStatus() != EPathFollowingStatus::Moving)
	{
		FNavLocation NavLocationResult;
		if (NavArea->GetRandomReachablePointInRadius(GetCharacter()->GetActorLocation(), RandomMoveRange, NavLocationResult))
		{
			MoveToLocation(NavLocationResult.Location);
		}
	}

	// start timer to continue its job
	GetWorldTimerManager().UnPauseTimer(MoveThreadTimerHandle);
}

void ASFRAIController::ShootThread()
{
	
}
