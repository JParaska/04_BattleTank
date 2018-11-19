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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		// Not specifying DoNotTrace causes bug...

		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	// TODO fix crossair color 
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;		
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	// First fire after initial reload
	LastFireTime = FPlatformTime::Seconds();
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
	// Rotate turret the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		if (!ensure(Barrel)) return;
		if (!ensure(Projectile)) return;

		// Spawn projectile
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		if (!ensure(SpawnedProjectile)) return;

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !Barrel->GetForwardVector().Equals(AimDirection, .01f);
}