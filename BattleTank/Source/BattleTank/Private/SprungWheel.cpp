// Copyright Ivanov Andrey.

#include "SprungWheel.h"

#include "Kismet/GameplayStatics.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	*/

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Mass);

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	MassWheelConstraint->SetupAttachment(Mass);
	// MassWheelConstraint->SetConstrainedComponents(Mass, FName("Mass"), Wheel, FName("Wheel"));

	MassWheelConstraint->ComponentName1.ComponentName = FName("Mass");
	MassWheelConstraint->ComponentName2.ComponentName = FName("Wheel");

	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);
	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);
	MassWheelConstraint->SetLinearDriveParams(50.f, 20.f, 0);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
