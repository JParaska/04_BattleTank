// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PTank = GetPlayerTank();
	if (PTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI found Player controlled Tank: %s"), *PTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Player controlled Tank"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

