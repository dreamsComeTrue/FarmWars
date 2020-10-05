#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

UCLASS()
class FARMWARS_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalCharacter();

	UFUNCTION(BlueprintNativeEvent)
		void MoveAnimation(bool shouldPlay);

	virtual void MoveAnimation_Implementation(bool shouldPlay);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
		FGuid Guid;

	UPROPERTY(EditAnywhere)
		class UWidgetComponent* GrabWidgetComponent;

	UPROPERTY(EditAnywhere) 
		TArray<class UStaticMesh*> StaticMeshes;
};
