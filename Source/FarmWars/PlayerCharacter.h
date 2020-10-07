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

	void UpdateInventoryItemTransform();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
		void MoveAnimation(bool shouldPlay);

	virtual void MoveAnimation_Implementation(bool shouldPlay);

	void SetPotentialInventoryItem(class AAnimalCharacter* Item);
	void ClearPotentialInventoryItem();

	class AAnimalCharacter* GetInventoryItem() { return InventoryItem; }

	UFUNCTION(BlueprintNativeEvent)
		void InventoryItemChanged(class AAnimalCharacter* InventoryItem);

	virtual void InventoryItemChanged_Implementation(class AAnimalCharacter* InventoryItem);

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

	class AAnimalCharacter* PotentialInventoryItem;

	bool bMovingForward = false;
	bool bMovingSideways = false;

public:
	UPROPERTY(BlueprintReadOnly)
		class AAnimalCharacter* InventoryItem;
};
