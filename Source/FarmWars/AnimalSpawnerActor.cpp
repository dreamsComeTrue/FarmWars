#include "AnimalSpawnerActor.h"
#include "AnimalCharacter.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AAnimalSpawnerActor::AAnimalSpawnerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentActorsCount = 0;
	SpawnRate = 10.0f;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
}

void AAnimalSpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AAnimalSpawnerActor::SpawnAnimal, SpawnRate, true, 2.0f);
}

void AAnimalSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalSpawnerActor::SpawnAnimal()
{
	FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(TriggerBox->GetComponentLocation(), 
		TriggerBox->GetScaledBoxExtent());
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AAnimalCharacter>(AnimalBlueprintType.Get(), Location, Rotation, SpawnInfo);
}

