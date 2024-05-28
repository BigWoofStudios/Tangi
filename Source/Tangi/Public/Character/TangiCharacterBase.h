// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "MotionWarpingComponent.h"
#include "CharacterTrajectoryComponent.h"
#include "Combat/CombatInterface.h"
#include "GameFramework/Character.h"
#include "TangiCharacterBase.generated.h"

class UTangiAbilityTagMapping;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class TANGI_API ATangiCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ATangiCharacterBase();

	virtual UStaticMeshComponent* GetActiveWeaponMesh() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void DeathTagChanged(const FGameplayTag CallbackTag, const int32 NewCount);
	
	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS|Ability")
	TObjectPtr<UTangiAbilityTagMapping> TagRelationshipMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* SecondWeaponMesh;

	UPROPERTY(BlueprintReadOnly)
	UMotionWarpingComponent* MotionWarping = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UCharacterTrajectoryComponent* CharacterTrajectory = nullptr;
	
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


// ---------------------------------------------------------------------------------------------------------------------
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
public:
	UFUNCTION()
	FORCEINLINE bool GetIsDead() const { return bIsDead; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Montages")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Combat")
	bool bIsDead = false;

	void SetIsDead(const bool bNewIsDead);

	UFUNCTION(Server, Reliable) void ServerSetIsDead(bool bNewIsDead);
#pragma endregion
};
