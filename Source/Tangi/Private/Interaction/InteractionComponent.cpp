// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Interaction/InteractionComponent.h"

#include "Interaction/InteractionInterface.h"
#include "Tangi/Tangi.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (const APlayerController* PlayerController = Cast<APlayerController>(Owner))
	{
		OwningActor = PlayerController->GetPawn();
	}
	else
	{
		OwningActor = Owner;
	}
}

void UInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForInteractionTarget();
}

void UInteractionComponent::CheckForInteractionTarget()
{
	if (!IsValid(OwningActor)) return;
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	FHitResult HitResult;
	FVector TraceStart;
	FRotator TraceRotation;
	OwningActor->GetActorEyesViewPoint(TraceStart, TraceRotation);
	const FVector TraceEnd = TraceStart + TraceRotation.Vector() * MaxInteractionDistance;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(GetOwner());
	
	World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Interaction, Params);

	if (AActor* HitActor = HitResult.GetActor())
	{
		// Ignore the actor if it is already the focused target
		if (HitActor == InteractionTarget) return;
		if (HitActor == OwningActor) return;

		if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(HitActor))
		{
			if ()
			// Switch focus and update the interaction target
			if (InteractionTarget) Cast<IInteractionInterface>(InteractionTarget)->EndFocus();
			InteractionInterface->BeginFocus();
			InteractionTarget = HitActor;
			return;
		}
	}

	// Reset InteractionTarget when the hit actor isn't interactable
	if (InteractionTarget) Cast<IInteractionInterface>(InteractionTarget)->EndFocus();
	InteractionTarget = nullptr;
}

void UInteractionComponent::Interact()
{
	ServerInteract(InteractionTarget);
}

void UInteractionComponent::ServerInteract_Implementation(AActor* Target)
{
	if (const IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
	{
		InteractionInterface->Execute_Interact(Target, OwningActor);
		MulticastInteract(Target);
	}
}

void UInteractionComponent::MulticastInteract_Implementation(AActor* Target)
{
	if (const IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
	{
		InteractionInterface->Execute_Interact(Target, OwningActor);
	}
}