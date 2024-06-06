// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/BaseInteractableActor.h"
#include "TangiBaseItem.generated.h"

UCLASS()
class TANGI_API ATangiBaseItem : public ABaseInteractableActor
{
	GENERATED_BODY()
	
public:	
	ATangiBaseItem();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	FName RowName = FName();

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Quantity = 1;
	
	virtual void HandleInteract() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
