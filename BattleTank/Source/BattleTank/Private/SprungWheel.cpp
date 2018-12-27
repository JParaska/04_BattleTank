// Jan Paraska

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(MassWheelConstraint);

	AxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axel Constraint"));
	AxelConstraint->SetupAttachment(Axel);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(AxelConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axel->GetForwardVector()*ForceMagnitude);
}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) return;
	auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);

	AxelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
}