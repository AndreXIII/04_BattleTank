// Copyright Ivanov Andrey.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"


UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const; // TODO implement throw components

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);

	FMortarDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	AMortar();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100; // TODO implement throw components

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // TODO implement throw components
};
