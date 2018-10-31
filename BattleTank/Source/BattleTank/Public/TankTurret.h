// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
/** Properties */
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 25;

/** Methods */
public:
	// -1 is max leftwards speed, +1 is max rightwards speed
	void Rotate(float RelativeSpeed);
	
};
