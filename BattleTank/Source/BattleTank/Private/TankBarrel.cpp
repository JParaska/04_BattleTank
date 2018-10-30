// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Elevate barrel
	UE_LOG(LogTemp, Warning, TEXT("%f: Aiming..."), GetWorld()->GetTimeSeconds());
}
