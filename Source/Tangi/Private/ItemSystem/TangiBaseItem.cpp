// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "ItemSystem/TangiBaseItem.h"

#include "ItemSystem/ItemSystemInterface.h"
#include "Net/UnrealNetwork.h"

ATangiBaseItem::ATangiBaseItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	InteractionDuration = 0.f;
}

void ATangiBaseItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, RowName, Parameters);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, Quantity, Parameters);
}

void ATangiBaseItem::HandleInteract()
{
	// Pickup functionality
	if (IItemSystemInterface* ItemSystemInterface = Cast<IItemSystemInterface>(InteractingActor))
	{
		if (ItemSystemInterface->GetBag()->PickUpItem(this))
		{
			// If a specific quantity needs to be picked up, it needs to be handled here.
			// and the PickUpItem implementation should return the amount left over.
			Destroy();
		}
	}
	
	// No need for Super::HandleInteract() b/c this actor implements
	// the interact functionality in C++.
	EndInteract();
}

void ATangiBaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ATangiBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

