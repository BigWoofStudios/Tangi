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

	UFUNCTION() void BeginInteract();
	UFUNCTION() void EndInteract();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxInteractionDistance = 250.f;

protected:
	virtual void BeginPlay() override;
		
private:
	
	UFUNCTION() void CheckForInteractionTarget();
	UPROPERTY() TObjectPtr<AActor> OwningActor;
	UPROPERTY() TObjectPtr<AActor> InteractionTarget = nullptr;
	
	UFUNCTION(Server, Reliable) void ServerBeginInteract(AActor* Target, AActor* OtherActor);
	UFUNCTION(NetMulticast, Reliable) void MulticastBeginInteract(AActor* Target, AActor* OtherActor);

	UFUNCTION(Server, Reliable) void ServerEndInteract(AActor* Target);
	UFUNCTION(NetMulticast, Reliable) void MulticastEndInteract(AActor* Target);

	void ResetInteraction();
};
