// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Actor/BaseInteractableActor.h"

ABaseInteractableActor::ABaseInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ABaseInteractableActor::BeginFocus()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("BeginFocus"));
}

void ABaseInteractableActor::EndFocus()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("EndFocus"));
}

bool ABaseInteractableActor::IsInteractable(const AActor* OtherActor)
{
	// Cannot interact with self
	if (this == OtherActor) return false;
	
	// Prevent interaction while being interacted with
	if (IsValid(InteractingActor)) return false;

	return true;
}

void ABaseInteractableActor::BeginInteract(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("BeginInteract"));
	if (InteractingActor) return;

	InteractingActor = OtherActor;
	if (GetInteractionDuration() <= 0.f)
	{
		HandleInteract();
	}
	else
	{
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
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("EndInteract"));
	GetWorldTimerManager().ClearTimer(InteractionTimer);
	InteractionTimer.Invalidate();
	InteractingActor = nullptr;
}

void ABaseInteractableActor::HandleInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("HandleInteract"));
	Execute_Interact(this, InteractingActor);
	EndInteract();
}
