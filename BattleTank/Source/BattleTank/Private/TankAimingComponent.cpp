// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		// Not specifying DoNotTrace causes bug...

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Turret) || !ensure(Barrel)) return;

	// Work out difference between current barrel roation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//Elevate barrel
	Barrel->Elevate(DeltaRotator.Pitch);
	// Rotate turret
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel || Projectile)) return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded) {
		// Spawn projectile
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		if (ensure(SpawnedProjectile)) {
			SpawnedProjectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	}
}