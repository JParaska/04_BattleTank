// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
/** Properties */
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0;

/** Methods */
public:
	// -1 is max downward speed, +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
};
