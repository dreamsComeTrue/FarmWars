#include "AnimalPawn.h"
#include "Components/StaticMeshComponent.h"
#include "AnimalPawnMovementComponent.h"

AAnimalPawn::AAnimalPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	MovementComponent = CreateDefaultSubobject<UAnimalPawnMovementComponent>(TEXT("MovementComponent"));

	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = RootComponent;
	}
}

void AAnimalPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AAnimalPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimalPawn::MoveAnimation_Implementation(bool shouldPlay)
{
}

UPawnMovementComponent* AAnimalPawn::GetMovementComponent() const
{
	return MovementComponent;
}
