#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

UENUM(BlueprintType)
enum LifeLevelType
{
	Spawned,	//	Initial state, takes 1st hit when falling on the ground from the sky
	FullLife,
	Damaged1,
	Damaged2,
	Destroyed
};

UCLASS()
class FARMWARS_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalCharacter();

	UFUNCTION(BlueprintNativeEvent)
		void MoveAnimation(bool shouldPlay);

	virtual void MoveAnimation_Implementation(bool shouldPlay);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
		void OnAnimalGrabbed();

	virtual void OnAnimalGrabbed_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
		void OnAnimalDropped();

	virtual void OnAnimalDropped_Implementation();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	bool Grab(class APlayerCharacter* Player);
	bool Drop(class APlayerCharacter* Player);

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UStaticMeshComponent* GetStaticMeshComponent() { return StaticMeshComponent; }

public:
	UPROPERTY(BlueprintReadOnly)
	class APlayerCharacter* OwningPlayer;

	UPROPERTY(EditAnywhere)
		class USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadWrite)
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
		FGuid Guid;

	UPROPERTY(EditAnywhere)
		class UWidgetComponent* GrabWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UStaticMesh*> StaticMeshes;

	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<LifeLevelType> LifeLevel;
};
