#include "PlayerCharacter.h"
#include "AnimalCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ActorSequence/Public/ActorSequencePlayer.h"
#include "ActorSequence/Public/ActorSequenceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

APlayerCharacter::APlayerCharacter()
{
	MovementSpeed = 400.0f;
	PrimaryActorTick.bCanEverTick = true;

	InventoryItem = nullptr;
	PotentialInventoryItem = nullptr;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(-240.0f, 0.0f, 100.0f));
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	StaticMeshComponent->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));
	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetReceivesDecals(false);
	StaticMeshComponent->SetupAttachment(SceneComponent);

	GetCapsuleComponent()->SetCapsuleHalfHeight(9.0f);
	GetCapsuleComponent()->SetCapsuleRadius(10.0f);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAnimation(bMovingForward || bMovingSideways);

	UpdateInventoryItemTransform();
}

void APlayerCharacter::UpdateInventoryItemTransform()
{
	//	Could have been done with Sockets and attachments as well
	if (InventoryItem)
	{
		FVector Location = this->GetActorLocation();
		Location.Z += 120;

		if (InventoryItem->GetActorLocation() != Location)
		{
			InventoryItem->SetActorLocationAndRotation(Location, this->GetControlRotation());
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpAction);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::InteractAction);
}

void APlayerCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (AxisValue < 0.0f)
	{
		StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		bMovingSideways = true;
	}
	else if (AxisValue > 0.0f)
	{
		StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		bMovingSideways = true;
	}
	else
	{
		bMovingSideways = false;
	}

	AController* Controller = GetController();
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (AxisValue < 0.0f)
	{
		StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		bMovingForward = true;
	}
	else if (AxisValue > 0.0f)
	{
		StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		bMovingForward = true;
	}
	else
	{
		bMovingForward = false;
	}

	AController* Controller = GetController();
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void APlayerCharacter::JumpAction()
{
	Jump();
}

void APlayerCharacter::InteractAction()
{
	if (InventoryItem)
	{
		AAnimalCharacter* CurrentItem = InventoryItem;

		InventoryItem = nullptr;
		CurrentItem->Drop(this);
	}
	else
	{
		if (PotentialInventoryItem != nullptr && PotentialInventoryItem->Grab(this))
		{
			InventoryItem = PotentialInventoryItem;
		}
	}

	InventoryItemChanged(InventoryItem);
}

void APlayerCharacter::SetPotentialInventoryItem(class AAnimalCharacter* Item)
{
	PotentialInventoryItem = Item;
}

void APlayerCharacter::ClearPotentialInventoryItem()
{
	PotentialInventoryItem = nullptr;
}

void APlayerCharacter::MoveAnimation_Implementation(bool shouldPlay)
{
}

void APlayerCharacter::InventoryItemChanged_Implementation(class AAnimalCharacter* InventoryItem)
{

}