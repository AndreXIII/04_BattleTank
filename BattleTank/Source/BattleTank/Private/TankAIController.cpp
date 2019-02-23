// Copyright Ivanov Andrey.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Mortar.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		if (auto PossessedTank = Cast<ATank>(InPawn))
		{
			if (!ensure(PossessedTank)) { return; }
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
		}
		else if (auto PossessedTank = Cast<AMortar>(InPawn))
		{
			if (!ensure(PossessedTank)) { return; }
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
		}
		else { return; }
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius in cm

	if (!ensure(TankAimingComponent)) { return; }
	// Aim towards the player
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
	{
		TankAimingComponent->Fire(); // TODO limit firing rate
	}
}
