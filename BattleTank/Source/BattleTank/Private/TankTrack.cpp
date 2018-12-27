// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack()
{
	
}

void UTankTrack::SetThrottle(float Throttle)
{
	DrivingTank(FMath::Clamp<float>(Throttle, -1, 1));
}

void UTankTrack::DrivingTank(float Throttle)
{
	auto ForceApplied = Throttle * TrackMaxDrivingForce;
	auto ForcePerWheel = ForceApplied / GetWheels().Num();
	for (auto Wheel : GetWheels()) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<class ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (auto Child : Children) {
		auto ChildSpawnPoint = Cast<USpawnPoint>(Child);
		if (ChildSpawnPoint) {
			auto Wheel = Cast<ASprungWheel>(ChildSpawnPoint->GetSpawnedWheel());
			if (Wheel) {
				ResultArray.Add(Wheel);
			}
		}
	}
	return ResultArray;
}
