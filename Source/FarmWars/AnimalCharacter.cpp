#include "AnimalCharacter.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine.h"

AAnimalCharacter::AAnimalCharacter()
{
	Guid = FGuid::NewGuid();

	PrimaryActorTick.bCanEverTick = true;
	OwningPlayer = nullptr;
	LifeLevel = LifeLevelType::Spawned;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetReceivesDecals(false);
	StaticMeshComponent->SetIsReplicated(true);
	StaticMeshComponent->SetupAttachment(SceneComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(80.0f, 80.0f, 32.0f));
	TriggerBox->SetupAttachment(SceneComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAnimalCharacter::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AAnimalCharacter::OnOverlapEnd);

	GrabWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GrabWidgetComponent"));
	GrabWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	GrabWidgetComponent->SetPivot(FVector2D::ZeroVector);
	GrabWidgetComponent->SetupAttachment(SceneComponent);
	GrabWidgetComponent->SetVisibility(false);

	GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
	GetCapsuleComponent()->SetCapsuleRadius(25.0f);
}

void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAnimalCharacter::MoveAnimation_Implementation(bool shouldPlay)
{
}

void AAnimalCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player && !Player->GetInventoryItem() && !OwningPlayer)
	{
		GrabWidgetComponent->SetVisibility(true);
		Player->SetPotentialInventoryItem(this);
	}
}

void AAnimalCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player && !OwningPlayer)
	{
		GrabWidgetComponent->SetVisibility(false);
		Player->ClearPotentialInventoryItem();
	}
}

bool AAnimalCharacter::Grab(APlayerCharacter* Player)
{
	if (OwningPlayer == nullptr)
	{
		OwningPlayer = Player;
		OnAnimalGrabbed();
		GrabWidgetComponent->SetVisibility(false);

		return true;
	}

	return false;
}

bool AAnimalCharacter::Drop(APlayerCharacter* Player)
{
	if (OwningPlayer != nullptr)
	{
		OnAnimalDropped();
		OwningPlayer = nullptr;

		return true;
	}

	return false;
}

float AAnimalCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Emerald, FString::FromInt(LifeLevel.GetValue()));

	switch (LifeLevel)
	{
	case LifeLevelType::Spawned:
		LifeLevel = LifeLevelType::FullLife;
		break;

	case LifeLevelType::FullLife:
		LifeLevel = LifeLevelType::Damaged1;
		break;

	case LifeLevelType::Damaged1:
		LifeLevel = LifeLevelType::Damaged2;
		break;

	case LifeLevelType::Damaged2:
		LifeLevel = LifeLevelType::Destroyed;
		break;

	case LifeLevelType::Destroyed:
		Destroy();
		break;
	}

	return 1.0f;
}

void AAnimalCharacter::OnAnimalGrabbed_Implementation()
{

}

void AAnimalCharacter::OnAnimalDropped_Implementation()
{

}