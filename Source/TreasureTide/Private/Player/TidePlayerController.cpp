// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TidePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
}

void ATidePlayerController::MoveTriggered(const FInputActionValue& ActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (!IsValid(ControlledPawn)) return;

	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, InputVector.ToString());
}
#pragma endregion 