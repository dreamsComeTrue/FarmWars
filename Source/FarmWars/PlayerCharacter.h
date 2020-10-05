#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FARMWARS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	void YawCamera(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void JumpAction();
	void InteractAction();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
	void MoveAnimation(bool shouldPlay);

	virtual void MoveAnimation_Implementation(bool shouldPlay);

	void SetInventoryItem(class AAnimalCharacter* Item);
	void ClearInventoryItem();

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	FVector2D CameraInput;
	FVector2D MovementInput;

	class AAnimalCharacter* InventoryItem;

	bool bMovingForward = false;
	bool bMovingSideways = false;
};
