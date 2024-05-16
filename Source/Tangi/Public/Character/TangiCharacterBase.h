// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TangiCharacterBase.generated.h"

class UTangiAbilityTagMapping;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class TANGI_API ATangiCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATangiCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	
	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS|Ability")
	TObjectPtr<UTangiAbilityTagMapping> TagRelationshipMapping;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const;
	virtual void InitializeDefaultAttributes();

	//~ Add startup abilities for the character
	void AddCharacterAbilities() const;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Attribute")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Attribute")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Ability", meta=(Description="These abilities will be granted on startup / when the ASC is associated."))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities = {};

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Montages")
	TObjectPtr<UAnimMontage> HitReactMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Montages")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;
};
