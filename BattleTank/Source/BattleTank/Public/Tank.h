// JP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

/** Properties */
protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing) // TODO make Categories to be Strings
	float LaunchSpeed = 8000; // TODO find sensible default launch speed (cm/s)

	UTankBarrel* Barrel = nullptr; // TODO get rid of this

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

/** Methods */
public:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Fire();

	void AimAt(FVector HitLocation);
};
