// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANGI_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginFocus() = 0;
	virtual void EndFocus() = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void Interact(AActor* OtherActor);

	virtual float GetInteractionDuration() = 0;

	virtual void BeginInteract(AActor* OtherActor) = 0;
	virtual void EndInteract() = 0;
	
	virtual bool IsInteractable(const AActor* OtherActor) = 0;

	virtual bool IsBeingInteractedWith() = 0;
};