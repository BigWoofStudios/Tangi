// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Player/TangiPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TangiGameplayTags.h"
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
	if (UTangiAbilitySystemComponent* TangiASC = GetTangiAbilitySystemComponent())
	{
		TangiASC->ProcessAbilityInput(DeltaTime, bGamePaused);
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

void ATangiPlayerController::ShowDamageNumber_Implementation(const float DamageAmount, ACharacter* TargetCharacter, const bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bCriticalHit);
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

	TangiInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MoveTriggered);
	TangiInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ThisClass::MoveStopped);
	TangiInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ThisClass::MoveStopped);
	TangiInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::LookTriggered);
	TangiInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::CrouchStarted);
	TangiInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::JumpStarted);
	TangiInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::InteractStarted);
	TangiInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ThisClass::InteractEnded);
	
	TangiInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased);
}

void ATangiPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
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
	if (GetTangiAbilitySystemComponent())
	{
		// Don't allow dead players to move
		if (TangiAbilitySystemComponent->HasMatchingGameplayTag(FTangiGameplayTags::Status_IsDead)) return;
		
		// Give the ASC the InputTag_Move GameplayTag when they are applying movement input
		if (!TangiAbilitySystemComponent->HasMatchingGameplayTag(FTangiGameplayTags::InputTag_Move))
		{
			TangiAbilitySystemComponent->AddLooseGameplayTag(FTangiGameplayTags::InputTag_Move);
			TangiAbilitySystemComponent->AddReplicatedLooseGameplayTag(FTangiGameplayTags::InputTag_Move);
		}
	}
	
	// Scale and clamp the input vector between 0 and 1
	const FVector2D Value = ActionValue.Get<FVector2D>().GetSafeNormal();
	const FVector ForwardDirection = UTangiMath::RadianToDirectionXY(FMath::DegreesToRadians(ControlledPawn->GetActorRotation().Yaw));
	const FVector RightDirection = UTangiMath::PerpendicularCounterClockwiseXY(ForwardDirection);

	ControlledPawn->AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}
void ATangiPlayerController::MoveStopped(const FInputActionValue&)
{
	if (GetTangiAbilitySystemComponent())
	{
		if (TangiAbilitySystemComponent->HasMatchingGameplayTag(FTangiGameplayTags::InputTag_Move))
		{
			TangiAbilitySystemComponent->RemoveReplicatedLooseGameplayTag(FTangiGameplayTags::InputTag_Move);
			TangiAbilitySystemComponent->RemoveLooseGameplayTag(FTangiGameplayTags::InputTag_Move);
		}
	}
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
