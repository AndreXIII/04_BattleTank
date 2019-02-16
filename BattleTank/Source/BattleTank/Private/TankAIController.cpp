// Copyright Ivanov Andrey.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius in cm

	if (!ensure(TankAimingComponent)) { return; }
	// Aim towards the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO Fix Fire
	// ControlledTank->Fire(); // TODO limit firing rate
}
