// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Actor/BaseInteractableActor.h"

#include "Net/UnrealNetwork.h"

ABaseInteractableActor::ABaseInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
	FocusWidget = CreateDefaultSubobject<UFocusWidget>("FocusWidget");
	FocusWidget->SetWidgetSpace(EWidgetSpace::Screen);
	FocusWidget->SetDrawAtDesiredSize(true);
	FocusWidget->bOnlyOwnerSee = true;
	FocusWidget->bHiddenInGame = true;
	FocusWidget->bHiddenInSceneCapture = true;
	FocusWidget->SetupAttachment(GetRootComponent());
}

void ABaseInteractableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseInteractableActor, InteractingActor);
}

void ABaseInteractableActor::BeginFocus()
{
	FocusWidget->SetHiddenInGame(false);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("BeginFocus"));
}

void ABaseInteractableActor::EndFocus()
{
	FocusWidget->SetOwnerPlayer(nullptr);
	FocusWidget->SetHiddenInGame(true);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("EndFocus"));
}

bool ABaseInteractableActor::IsInteractable(const AActor* OtherActor)
{
	// Cannot interact with self
	if (this == OtherActor) return false;
	
	// Prevent interaction while being interacted with
	if (IsBeingInteractedWith()) return false;
	
	return true;
}

void ABaseInteractableActor::BeginInteract(AActor* OtherActor)
{
	if (!IsInteractable(OtherActor)) return;

	InteractingActor = OtherActor;
	if (GetInteractionDuration() <= 0.f)
	{
		HandleInteract();
	}
	else
	{
		GetWorldTimerManager().SetTimer(DelegateInterval, this, &ABaseInteractableActor::HandleDelegate, 0.1f, true);
		GetWorldTimerManager().SetTimer(
		InteractionTimer,
		this,
		&ABaseInteractableActor::HandleInteract,
		GetInteractionDuration(),
		false,
		-1.f);
		
	}
}

void ABaseInteractableActor::EndInteract()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	InteractionTimer.Invalidate();
	DelegateInterval.Invalidate();
	FocusWidget->TimeRemaining = 0.f;
	InteractingActor = nullptr;
}

void ABaseInteractableActor::HandleDelegate()
{
	const float RemainingInteractionTime = GetWorldTimerManager().GetTimerElapsed(InteractionTimer);
	const float PercentComplete = (RemainingInteractionTime / GetInteractionDuration());
	// Delegate or maybe just call function on a widget class that needs to be defined.
	FocusWidget->TimeRemaining = PercentComplete;
}

void ABaseInteractableActor::HandleInteract()
{
	Execute_Interact(this, InteractingActor);
	EndInteract();
}
