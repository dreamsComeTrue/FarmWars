#include "AnimalPawnMovementComponent.h"
#include "Engine.h"

void UAnimalPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("PAWN MOVE"));

	FVector DesiredMovementThisFrame = GetPendingInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;

	const AController* Controller = PawnOwner->GetController();

	if (Controller)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, DesiredMovementThisFrame.ToCompactString());
	}

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
};