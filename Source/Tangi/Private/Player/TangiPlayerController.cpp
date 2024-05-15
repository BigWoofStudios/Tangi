// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TangiPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TangiMath.h"

ATangiPlayerController::ATangiPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = false;
}

void ATangiPlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	Super::BeginPlay();

	checkf(TangiContext, TEXT("TangiPlayerController requires an Input Mapping Context. Please check the BP for this member."));

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TangiContext, 0);
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Input
void ATangiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind input actions to functions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::MoveTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::LookTriggered);
}

void ATangiPlayerController::MoveTriggered(const FInputActionValue& ActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!IsValid(ControlledPawn)) return;

	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	
	// Scale and clamp the input vector between 0 and 1
	const FVector2D Value = UTangiMath::ClampMagnitude012D(InputVector);

	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, Value.ToString());

	const FVector ForwardDirection = UTangiMath::AngleToDirectionXY(UE_REAL_TO_FLOAT(ControlledPawn->GetActorRotation().Yaw));
	const FVector RightDirection = UTangiMath::PerpendicularCounterClockwiseXY(ForwardDirection);
	ControlledPawn->AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void ATangiPlayerController::LookTriggered(const FInputActionValue& ActionValue)
{
	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	AddYawInput(InputVector.X);
	AddPitchInput(InputVector.Y);
}
#pragma endregion 
