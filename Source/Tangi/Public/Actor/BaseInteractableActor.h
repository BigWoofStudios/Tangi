// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractionInterface.h"
#include "BaseInteractableActor.generated.h"

UCLASS()
class TANGI_API ABaseInteractableActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ABaseInteractableActor();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual bool IsInteractable(const AActor* OtherActor) override;
};
