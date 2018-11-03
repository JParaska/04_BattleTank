// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at player
		if (ControlledTank) {
			ControlledTank->AimAt(PlayerTank->GetActorLocation());

			// Fire if ready
			ControlledTank->Fire(); // TODO do not fire every frame
		}
	}
}

