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
	if (this == OtherActor) return false;


	return true;
}
