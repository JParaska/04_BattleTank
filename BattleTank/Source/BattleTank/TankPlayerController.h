// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

/** Properties */
private:

	UPROPERTY(EditAnywhere)
	float CrossHairX = .5;

	UPROPERTY(EditAnywhere)
	float CrossHairY = .33;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; //cm = 10KM
	
/** Methods */
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	ATank* GetControlledTank() const;

	// Move barrel and turret where the crosshair intersecst the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector & OutHitLocation);

	// Deproject screen position of the crosshair to the world direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector& HitLocation, FVector& LookLocation, FVector LookDirection) const;
	//bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;
};
