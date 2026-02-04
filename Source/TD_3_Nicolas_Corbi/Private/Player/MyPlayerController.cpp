#include "Player/MyPlayerController.h"
#include "Player/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!MappingContext)
	{
		return;
	}

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EILPS = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			EILPS->AddMappingContext(MappingContext, 0);
		}
	}

	MyChara = Cast<AMyCharacter>(GetPawn());

	if (MyChara && MyChara->GetCharacterMovement())
	{
		DefaultMaxSpeed = MyChara->GetCharacterMovement()->MaxWalkSpeed;
	}

	PlayerCameraManager->ViewPitchMin = -45;

	PlayerCameraManager->ViewPitchMax = 45;

	SetShowMouseCursor(false);

	SetInputMode(GameOnly);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (FInputData data : InputDataList)
		{
			EIC->BindAction(data.Action, data.Event, this, data.ActionName.GetMemberName());
		}
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	FVector Movement = Value.Get<FVector>();

	FRotator CameraRotation = FRotator(0, GetControlRotation().Yaw, 0);

	MyChara->AddMovementInput(CameraRotation.RotateVector(Movement));
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D Values = Value.Get<FVector2D>();

	AddYawInput(Values.X * CameraSensitivity * GetWorld()->GetDeltaSeconds());

	AddPitchInput(Values.Y * CameraSensitivity * GetWorld()->GetDeltaSeconds());
}

void AMyPlayerController::Jump(const FInputActionValue& Value)
{
	MyChara->Jump();
}

void AMyPlayerController::SprintStart(const FInputActionValue& Value)
{
	MyChara->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed * PlayerSprintFactor;
}

void AMyPlayerController::SprintEnd(const FInputActionValue& Value)
{
	MyChara->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;
}

void AMyPlayerController::Attack(const FInputActionValue& Value)
{
	MyChara->TryAttack();
}
