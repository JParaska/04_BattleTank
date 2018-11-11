// JP

#include "../Public/Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("JanBT: %s constructor C++"), *GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("JanBT: %s Begin Play C++"), *GetName());
}

void ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComponent)) {
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::Fire()
{
	if (!ensure(Barrel)) return;

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
