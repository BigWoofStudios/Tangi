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
			Destroy();
		}
	}
	
	// No Super::HandleInteract() b/c this C++ actor implements the interact functionality.
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

