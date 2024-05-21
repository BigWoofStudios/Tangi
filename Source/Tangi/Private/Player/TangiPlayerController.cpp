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
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	AddOwnedComponent(InteractionComponent);
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

	TangiInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::MoveTriggered);
	TangiInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATangiPlayerController::LookTriggered);
	TangiInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATangiPlayerController::CrouchStarted);
	TangiInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATangiPlayerController::JumpStarted);
	TangiInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATangiPlayerController::InteractStarted);
	TangiInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ATangiPlayerController::InteractEnded);
	
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
	const FVector ForwardDirection = UTangiMath::AngleToDirectionXY(UE_REAL_TO_FLOAT(ControlledPawn->GetActorRotation().Yaw));
	const FVector RightDirection = UTangiMath::PerpendicularCounterClockwiseXY(ForwardDirection);

	ControlledPawn->AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void ATangiPlayerController::LookTriggered(const FInputActionValue& ActionValue)
{
	if (const APawn* ControlledPawn = GetPawn(); !IsValid(ControlledPawn)) return;
	
	const FVector2D InputVector = ActionValue.Get<FVector2D>();
	AddYawInput(InputVector.X);
	AddPitchInput(InputVector.Y);
}

void ATangiPlayerController::CrouchStarted(const FInputActionValue&)
{
	ACharacter* ControlledCharacter = GetCharacter();
	if (!IsValid(ControlledCharacter)) return;
	// TODO
}

void ATangiPlayerController::JumpStarted(const FInputActionValue& ActionValue)
{
	const bool InputValue = ActionValue.Get<bool>();
	ACharacter* ControlledCharacter = GetCharacter();
	if (!IsValid(ControlledCharacter)) return;
	
	if (InputValue)
	{
		ControlledCharacter->Jump();
	}
	else
	{
		ControlledCharacter->StopJumping();
	}
}

void ATangiPlayerController::InteractStarted(const FInputActionValue&)
{
	InteractionComponent->BeginInteract();
}

void ATangiPlayerController::InteractEnded(const FInputActionValue&)
{
	InteractionComponent->EndInteract();
}
#pragma endregion 
