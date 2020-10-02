#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AnimalPawn.generated.h"

UCLASS()
class FARMWARS_API AAnimalPawn : public APawn
{
	GENERATED_BODY()

public:
	AAnimalPawn();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void MoveAnimation(bool shouldPlay);

	virtual void MoveAnimation_Implementation(bool shouldPlay);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class UAnimalPawnMovementComponent* MovementComponent;
};
