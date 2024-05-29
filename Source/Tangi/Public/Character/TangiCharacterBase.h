// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "MotionWarpingComponent.h"
#include "CharacterTrajectoryComponent.h"
#include "Combat/CombatInterface.h"
#include "GameFramework/Character.h"
#include "HAL/CriticalSection.h"
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
	
	virtual void Tick(const float DeltaSeconds) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	
#pragma region Combat Interface
	virtual UStaticMeshComponent* GetActiveWeaponMesh() override { return TestWeapon; }
	virtual UAnimMontage* GetDeathMontage() override { return DeathMontage; }
	virtual TArray<USoundBase*> GetDeathSounds() override { return DeathSounds; }
	virtual bool GetIsDead() override { return bDead; }
	virtual UAnimMontage* GetHitReactMontage() override { return HitReactMontage; }
	virtual TArray<USoundBase*> GetHitReactSounds() override { return HitReactSounds; }
	virtual bool GetIsHitReacting() override { return bHitReacting; }
#pragma endregion 
	
	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS|Ability")
	TObjectPtr<UTangiAbilityTagMapping> TagRelationshipMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* TestWeapon;

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
	
	// Critical section to ensure thread safety
	mutable FCriticalSection ConditionCriticalSection;
	
// ---------------------------------------------------------------------------------------------------------------------
// Hit React
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Hit React
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe)) uint8 GetHitReacting() const
	{
		FScopeLock Lock(&ConditionCriticalSection);
		return bHitReacting;
	}
	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, const int32 NewCount);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Hit React")
	TObjectPtr<UAnimMontage> HitReactMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Hit React")
	TArray<USoundBase*> HitReactSounds = {};
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "Combat|Hit React")
	uint8 bHitReacting: 1 = 0;

	void SetHitReacting(const bool NewValue);
	UFUNCTION(Server, Reliable) void ServerSetHitReacting(const bool NewValue);
#pragma endregion
	
// ---------------------------------------------------------------------------------------------------------------------
// Death
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Death
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe)) uint8 GetDead() const
	{
		FScopeLock Lock(&ConditionCriticalSection);
		return bDead;
	}
	virtual void DeathTagChanged(const FGameplayTag CallbackTag, const int32 NewCount);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Death")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Death")
	TArray<USoundBase*> DeathSounds = {};
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "Combat|Death")
	uint8 bDead: 1 = 0;

	void SetDead(const bool NewValue);
	UFUNCTION(Server, Reliable) void ServerSetDead(const bool NewValue);
#pragma endregion

// ---------------------------------------------------------------------------------------------------------------------
// Swimming
// ---------------------------------------------------------------------------------------------------------------------
#pragma region Swimming
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe)) uint8 GetSwimming() const
	{
		FScopeLock Lock(&ConditionCriticalSection);
		return bSwimming;
	}
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe)) uint8 GetUnderwater() const {
		FScopeLock Lock(&ConditionCriticalSection);
		return bUnderwater;
	}
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "State|Swimming|Effect")
	TSubclassOf<UGameplayEffect> GE_HoldBreath = nullptr;
	
	void SetSwimming(const bool NewValue);
	UFUNCTION(Server, Reliable) void ServerSetSwimming(const bool NewValue);
	
	void SetUnderwater(const bool NewValue);
	UFUNCTION(Server, Reliable) void ServerSetUnderwater(const bool NewValue);
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "State|Swimming", Transient)
	uint8 bUnderwater: 1 = 0;
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "State|Swimming", Transient)
	uint8 bSwimming: 1 = 0;
	
	UFUNCTION() void RefreshSwimming();
#pragma endregion 
};
