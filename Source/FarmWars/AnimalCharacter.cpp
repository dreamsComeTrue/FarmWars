#include "AnimalCharacter.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

AAnimalCharacter::AAnimalCharacter()
{
	Guid = FGuid::NewGuid();

	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
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

	if (StaticMeshes.Num() != 0)
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshes[FMath::FRand() * StaticMeshes.Num()]);
	}
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

	if (Player)
	{
		GrabWidgetComponent->SetVisibility(true);
		Player->SetInventoryItem(this);
	}
}

void AAnimalCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		GrabWidgetComponent->SetVisibility(false);
		Player->ClearInventoryItem();
	}
}