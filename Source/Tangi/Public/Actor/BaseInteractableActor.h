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

	//~ Begin IInteractionInterface
	virtual bool IsInteractable(const AActor* OtherActor) override;
	
	virtual float GetInteractionDuration() override { return InteractionDuration; }
	
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	
	virtual void BeginInteract(AActor* OtherActor) override;
	virtual void EndInteract() override;
	//~ End IInteractionInterface
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(Description="The instigator of the current interation."))
	AActor* InteractingActor = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionDuration = 0.f;

private:
	FTimerHandle InteractionTimer;
	void HandleInteract();
};
