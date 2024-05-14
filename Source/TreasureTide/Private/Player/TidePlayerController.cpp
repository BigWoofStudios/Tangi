// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TidePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TideMath.h"

ATidePlayerController::ATidePlayerController()
{
	bReplicates = true;
	bShowMouseCursor = false;
}

void ATidePlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	Super::BeginPlay();

	checkf(TideContext, TEXT("TidePlayerController requires an Input Mapping Context. Please check the BP for this member."));

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TideContext, 0);
	}
}

// ---------------------------------------------------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Input
void ATidePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind input actions to functions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATidePlayerController::MoveTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATidePlayerController::LookTriggered);
}

void ATidePlayerController::MoveTriggered(const FInputActionValue& ActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!IsValid(ControlledPawn)) return;

	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	
	// Scale and clamp the input vector between 0 and 1
	const FVector2D Value = UTideMath::ClampMagnitude012D(InputVector);

	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, Value.ToString());

	const FVector ForwardDirection = UTideMath::AngleToDirectionXY(UE_REAL_TO_FLOAT(ControlledPawn->GetActorRotation().Yaw));
	const FVector RightDirection = UTideMath::PerpendicularCounterClockwiseXY(ForwardDirection);
	ControlledPawn->AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void ATidePlayerController::LookTriggered(const FInputActionValue& ActionValue)
{
	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	AddYawInput(InputVector.X);
	AddPitchInput(InputVector.Y);
}
#pragma endregion 
