// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Interaction/BaseInteractableActor.h"
#include "Net/UnrealNetwork.h"

ABaseInteractableActor::ABaseInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
	FocusWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("FocusWidgetComponent");
	FocusWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	FocusWidgetComponent->SetDrawAtDesiredSize(true);
	FocusWidgetComponent->bOnlyOwnerSee = true;
	FocusWidgetComponent->bHiddenInGame = true;
	FocusWidgetComponent->bHiddenInSceneCapture = true;
	FocusWidgetComponent->SetupAttachment(GetRootComponent());
}

void ABaseInteractableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseInteractableActor, InteractingActor);
}

void ABaseInteractableActor::BeginFocus()
{
	FocusWidgetComponent->SetHiddenInGame(false);
}

void ABaseInteractableActor::EndFocus()
{
	FocusWidgetComponent->SetHiddenInGame(true);
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
		GetWorldTimerManager().SetTimer(DelegateInterval, this, &ABaseInteractableActor::HandleDelegate, 0.03333f, true);
		GetWorldTimerManager().SetTimer(InteractionTimer, this, &ABaseInteractableActor::HandleInteract, GetInteractionDuration());
	}
}

void ABaseInteractableActor::EndInteract()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	InteractionTimer.Invalidate();
	DelegateInterval.Invalidate();
	FocusWidget->PercentComplete = 0.f;
	InteractingActor = nullptr;
}

bool ABaseInteractableActor::CanEditChange(const FProperty* InProperty) const
{
		
	return Super::CanEditChange(InProperty);
}

void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	if (FocusWidget)
	{
		FocusWidgetComponent->SetWidget(FocusWidget);
	}
}


void ABaseInteractableActor::HandleDelegate()
{
	const float RemainingInteractionTime = GetWorldTimerManager().GetTimerElapsed(InteractionTimer);
	const float PercentComplete = (RemainingInteractionTime / GetInteractionDuration());
	FocusWidget->PercentComplete = PercentComplete;
}

void ABaseInteractableActor::HandleInteract()
{
	Execute_Interact(this, InteractingActor);
	EndInteract();
}
