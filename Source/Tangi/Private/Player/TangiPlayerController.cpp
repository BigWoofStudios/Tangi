// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TangiPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TangiMath.h"
#include "GameFramework/Character.h"
#include "Input/TangiInputComponent.h"
#include "UI/Widget/DamageTextComponent.h"

ATangiPlayerController::ATangiPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = false;
}

void ATangiPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UTangiAbilitySystemComponent* VeilASC = GetTangiAbilitySystemComponent())
	{
		VeilASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

UTangiAbilitySystemComponent* ATangiPlayerController::GetTangiAbilitySystemComponent()
{
	if (TangiAbilitySystemComponent == nullptr)
    	{
    		TangiAbilitySystemComponent = Cast<UTangiAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    	}
    
    	return TangiAbilitySystemComponent;
}

void ATangiPlayerController::ShowDamageNumber_Implementation(const float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
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
	UTangiInputComponent* TangiInputComponent = CastChecked<UTangiInputComponent>(InputComponent);

	// Bind input actions to functions
	TangiInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::MoveTriggered);
	TangiInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::LookTriggered);
	
	TangiInputComponent->BindAbilityActions(InputConfig, this, &ATangiPlayerController::AbilityInputTagPressed, &ATangiPlayerController::AbilityInputTagReleased);
}

void ATangiPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	UTangiAbilitySystemComponent* ASC = GetTangiAbilitySystemComponent();
	if (!ASC) return;
	
	ASC->AbilityInputTagPressed(InputTag);
}

void ATangiPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	UTangiAbilitySystemComponent* ASC = GetTangiAbilitySystemComponent();
	if (!ASC) return;
	
	ASC->AbilityInputTagReleased(InputTag);
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
