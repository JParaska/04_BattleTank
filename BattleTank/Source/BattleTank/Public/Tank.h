// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

/** Properties */
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000; // TODO find sensible default launch speed (cm/s)

	UTankBarrel* Barrel = nullptr; // Place to spawn projectile

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

/** Methods */
public:
	// Sets default values for this pawn's properties
	ATank();	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	void AimAt(FVector HitLocation);

protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
