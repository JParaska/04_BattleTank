// JP

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::TankDestroyed);
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) return;
	FVector HitLocation = FVector(); // Out parameter

	// If hits landscape
	if (GetSightRayHitLocation(HitLocation)) { // Get world location of line trace through crosshair		
		AimingComponent->AimAt(HitLocation);
	}		
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) // TODO fix aiming
{
	/// Find crosshair position on screen
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairX, ViewportSizeY * CrossHairY);
	
	FVector LookLocation;
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookLocation, LookDirection)) {
		return GetLookVectorHitLocation(OutHitLocation, LookLocation, LookDirection);
		//return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	// Linetrace along that look direction and see what we hit (up to range)
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& LookDirection) const
{
	/*FVector LookLocation*/; // to be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, FVector& LookLocation, FVector LookDirection) const
//bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult Hit;
	//auto LookLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(Hit, LookLocation, LookLocation + LookDirection * LineTraceRange, ECollisionChannel::ECC_Visibility)) {
		HitLocation = Hit.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::TankDestroyed()
{
	StartSpectatingOnly();
}
