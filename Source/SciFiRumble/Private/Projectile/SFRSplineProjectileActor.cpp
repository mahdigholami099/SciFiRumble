// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SFRSplineProjectileActor.h"

#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ASFRSplineProjectileActor::ASFRSplineProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));
	Spline->SetupAttachment(Root);
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile"));
	ProjectileMesh->SetupAttachment(Root);
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(FName("TriggerSphere"));
	TriggerSphere->SetupAttachment(ProjectileMesh);
	
	ProjectileMesh->SetHiddenInGame(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
}

void ASFRSplineProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASFRSplineProjectileActor::FireTheProjectile, LaunchTimeDelay);

	Spline->ClearSplinePoints();
}

void ASFRSplineProjectileActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FPredictProjectilePathParams PredictProjectilePathParams;
	PredictProjectilePathParams.LaunchVelocity = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LaunchTarget+GetActorLocation())) * Velocity;
	PredictProjectilePathParams.StartLocation = GetActorLocation();

	FPredictProjectilePathResult PredictProjectilePathResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictProjectilePathParams, PredictProjectilePathResult);

	Spline->ClearSplinePoints();
	for (FPredictProjectilePathPointData& PathData : PredictProjectilePathResult.PathData)
	{
		Spline->AddSplineWorldPoint(PathData.Location);
	}
	
	for (int i = PredictRange; i > 1; --i)
	{
		PredictProjectilePathParams.LaunchVelocity = PredictProjectilePathResult.LastTraceDestination.Velocity;
		PredictProjectilePathParams.StartLocation = PredictProjectilePathResult.LastTraceDestination.Location;
		
		UGameplayStatics::PredictProjectilePath(GetWorld(), PredictProjectilePathParams, PredictProjectilePathResult);

		for (FPredictProjectilePathPointData& PathData : PredictProjectilePathResult.PathData)
		{
			Spline->AddSplineWorldPoint(PathData.Location);
		}
	}
}

void ASFRSplineProjectileActor::FireTheProjectile()
{
	OnProjectileFire();
	ProjectileMesh->SetHiddenInGame(false);
	ProjectileMovementComponent->Velocity = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LaunchTarget+GetActorLocation())) * Velocity;
	ProjectileMovementComponent->SetActive(true);
}

void ASFRSplineProjectileActor::OnProjectileFire_Implementation()
{
}
