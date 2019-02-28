// Copyright Ivanov Andrey.

#include "SprungWheel.h"

#include "Kismet/GameplayStatics.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(MassWheelConstraint);

	Axis = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axis"));
	Axis->SetupAttachment(Sphere);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Sphere);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		ForseMagnitudeToApply = 0;
	}
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Sphere, NAME_None);
	Axis->SetConstrainedComponents(Sphere, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::AddDrivingForce(float ForseMagnitude)
{
	ForseMagnitudeToApply += ForseMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Wheel->AddForce(Axis->GetForwardVector() * ForseMagnitudeToApply);
}
