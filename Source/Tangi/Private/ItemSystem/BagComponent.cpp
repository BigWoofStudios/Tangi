// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "ItemSystem/BagComponent.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

UBagComponent::UBagComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBagComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams Parameters;
	
	Parameters.bIsPushBased = true;
	Parameters.RepNotifyCondition = REPNOTIFY_OnChanged;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, Items, Parameters);
}

bool UBagComponent::PickUpItem(ATangiBaseItem* Item)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickUpItem must be called from the server."));
		return false;
	}
	// add item to Items array... todo, need to just find a slot
	Items.Add(Item);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Item->GetName());
	
	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, Items, this);
	return true;
}

void UBagComponent::BeginPlay()
{
	Super::BeginPlay();
}
