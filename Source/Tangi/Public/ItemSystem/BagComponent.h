// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TangiBaseItem.h"
#include "Components/ActorComponent.h"
#include "BagComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY()
	FString Name = FString();

	UPROPERTY()
	FString Description = FString();

	UPROPERTY()
	uint32 MaxStackSize = 1;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANGI_API UBagComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UBagComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	TArray<ATangiBaseItem*> GetItems() const { return Items; }

	bool PickUpItem(ATangiBaseItem* Item);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> ItemDataTable;
	
private:
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<ATangiBaseItem*> Items = {};
};
