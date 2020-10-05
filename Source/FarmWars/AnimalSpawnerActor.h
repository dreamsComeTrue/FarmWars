#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimalSpawnerActor.generated.h"

UCLASS()
class FARMWARS_API AAnimalSpawnerActor : public AActor
{
	GENERATED_BODY()

public:
	AAnimalSpawnerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SpawnAnimal();

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerBox;

	int CurrentActorsCount;

	UPROPERTY(EditAnywhere)
		int MaxActorsToSpawn;

	UPROPERTY(EditAnywhere)
		float SpawnRate;

	FTimerHandle SpawnerTimerHandle;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AAnimalCharacter> AnimalBlueprintType;
};
