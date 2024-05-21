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
			// Switch focus and update the interaction target
			ResetInteraction();
			InteractionInterface->BeginFocus();
			InteractionTarget = HitActor;
			return;
		}
	}

	// Reset InteractionTarget when the hit actor isn't interactable
	ResetInteraction();
}

void UInteractionComponent::ResetInteraction()
{
	EndInteract();
	InteractionTarget = nullptr;
}

void UInteractionComponent::BeginInteract()
{
	ServerBeginInteract(InteractionTarget, GetOwner());
}

void UInteractionComponent::ServerBeginInteract_Implementation(AActor* Target, AActor* OtherActor)
{
	if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
	{
		InteractionInterface->BeginInteract(OtherActor);
		MulticastBeginInteract(Target, OtherActor);
	}
}

void UInteractionComponent::MulticastBeginInteract_Implementation(AActor* Target, AActor* OtherActor)
{
	if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
	{
		InteractionInterface->BeginInteract(OtherActor);
	}
}

void UInteractionComponent::EndInteract()
{
	ServerEndInteract(InteractionTarget);
}

void UInteractionComponent::ServerEndInteract_Implementation(AActor* Target)
{
		if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
		{
			InteractionInterface->EndInteract();
			MulticastEndInteract(Target);
		}
}

void UInteractionComponent::MulticastEndInteract_Implementation(AActor* Target)
{
	if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(Target))
	{
		InteractionInterface->EndInteract();
	}
}