// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

/** Properties */
public:
	
/** Methods */
public:

	void BeginPlay() override;

	ATank* GetControlledTank() const;

	//void Tick(float DeltaTime) override;

};
