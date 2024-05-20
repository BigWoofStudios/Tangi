// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANGI_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Interact();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxInteractionDistance = 250.f;

protected:
	virtual void BeginPlay() override;
		
private:
	UFUNCTION()
	void CheckForInteractionTarget();

	UPROPERTY()
	TObjectPtr<AActor> OwningActor;
	
	UPROPERTY()
	TObjectPtr<AActor> InteractionTarget = nullptr;

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* Target);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastInteract(AActor* Target);
};
