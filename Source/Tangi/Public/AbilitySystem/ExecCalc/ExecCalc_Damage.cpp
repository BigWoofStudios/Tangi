// Copyright Big Woof Studios, LLC. All Rights Reserved.

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAttributeSet.h"

// Explicitly not adding the `F` in front because it isn't a USTRUCT, but rather internal to this file only.
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
struct TangiDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition CriticalHitChanceDef;
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	TangiDamageStatics()
	{
		CriticalHitChanceDef = FGameplayEffectAttributeCaptureDefinition(UTangiAttributeSet::GetCriticalHitChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		
		TagsToCaptureDefs.Add(FTangiGameplayTags::Attribute_Secondary_CriticalHitChance, CriticalHitChanceDef);
	}
};

static const TangiDamageStatics& DamageStatics()
{
	static TangiDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Source (Who is dealing the damage) -- Target (Who is receiving the damage)
	
	// const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	// const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	// AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	// AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	// Can be used to get info about the character that is related to combat
	// ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	// ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	// Can be used to get info about the character that is related to the items they possess or have equipped
	// IItemSystemInterface* SourceItemSystemInterface = Cast<IItemSystemInterface>(SourceAvatar);
	// IItemSystemInterface* TargetItemSystemInterface = Cast<IItemSystemInterface>(TargetAvatar);
 
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    	
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Damage = 10.f; // TODO: Get the actual damage set by caller magnitude

#pragma region Critical Hit
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Clamp(SourceCriticalHitChance, 0.f, 100.f);
	const bool bIsCriticalHit = FMath::RandRange(1, 100) < SourceCriticalHitChance;
	Damage = bIsCriticalHit ? Damage * 1.25f : Damage;
#pragma endregion
	
	const FGameplayModifierEvaluatedData EvaluatedData(UTangiAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
