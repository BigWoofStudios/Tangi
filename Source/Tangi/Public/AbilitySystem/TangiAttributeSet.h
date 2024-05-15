// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AbilitySystem/TangiGameplayEffectContext.h"
#include "TangiAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY() UAbilitySystemComponent *SourceASC = nullptr;
	UPROPERTY() AActor *SourceAvatarActor = nullptr;
	UPROPERTY() AController *SourceController = nullptr;
	UPROPERTY() ACharacter *SourceCharacter = nullptr;
	
	UPROPERTY() UAbilitySystemComponent *TargetASC = nullptr;
	UPROPERTY() AActor *TargetAvatarActor = nullptr;
	UPROPERTY() AController *TargetController = nullptr;
	UPROPERTY() ACharacter *TargetCharacter = nullptr;
};

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class TANGI_API UTangiAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTangiAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override;

	// A mapping between a gameplay tag and the function used to retrieve that attribute data
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagToAttribute;
	
private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties &Props);
	static void ShowFloatingText(const FEffectProperties &Props, const float Damage);
	
// -----------------------------------------------------------------------------------------------------------------
// Vital Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Vital Attributes
public:
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, Endurance);
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, Oxygen);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &OldHealth) const;
	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData &OldEndurance) const;
	UFUNCTION()
	void OnRep_Oxygen(const FGameplayAttributeData &OldOxygen) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, Category = "Attribute|Vital")
	FGameplayAttributeData Health;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Endurance, Category = "Attribute|Vital")
	FGameplayAttributeData Endurance;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Oxygen, Category = "Attribute|Vital")
	FGameplayAttributeData Oxygen;
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Secondary Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Secondary Attributes
public:
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, MaxEndurance);
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, MaxOxygen);

protected:
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxEndurance(const FGameplayAttributeData &OldMaxEndurance) const;
	UFUNCTION()
	void OnRep_MaxOxygen(const FGameplayAttributeData &OldMaxOxygen) const;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxHealth, Category = "Attribute|Vital")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxEndurance, Category = "Attribute|Vital")
	FGameplayAttributeData MaxEndurance;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MaxOxygen, Category = "Attribute|Vital")
	FGameplayAttributeData MaxOxygen;
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Meta Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Meta Attributes
public:
	ATTRIBUTE_ACCESSORS(UTangiAttributeSet, IncomingDamage);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Attribute|Meta")
	FGameplayAttributeData IncomingDamage;
#pragma endregion
};
