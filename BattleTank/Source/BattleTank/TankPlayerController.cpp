// JP

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) return;

	FVector HitLocation = FVector(); // Out parameter

	// If hits landscape
	if (GetSightRayHitLocation(HitLocation)) { // Get world location of line trace through crosshair		
		GetControlledTank()->AimAt(HitLocation);
	}		
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation)
{
	/// Find crosshair position on screen
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairX, ViewportSizeY * CrossHairY);
	
	FVector LookLocation;
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookLocation, LookDirection)) {
		if (GetLookVectorHitLocation(OutHitLocation, LookLocation, LookDirection)) return true;
		//if (GetLookVectorHitLocation(OutHitLocation, LookDirection)) return true;
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
