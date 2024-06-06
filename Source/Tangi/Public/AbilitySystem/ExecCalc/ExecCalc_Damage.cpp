// Copyright Big Woof Studios, LLC. All Rights Reserved.

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAbilitySystemLibrary.h"
#include "AbilitySystem/TangiAttributeSet.h"

struct FTangiDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition CriticalHitChanceDef;
	FGameplayEffectAttributeCaptureDefinition PhysicalResistanceDef;
	FGameplayEffectAttributeCaptureDefinition MagicResistanceDef;
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	FTangiDamageStatics()
	{
		CriticalHitChanceDef = FGameplayEffectAttributeCaptureDefinition(UTangiAttributeSet::GetCriticalHitChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		PhysicalResistanceDef = FGameplayEffectAttributeCaptureDefinition(UTangiAttributeSet::GetPhysicalResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
		MagicResistanceDef = FGameplayEffectAttributeCaptureDefinition(UTangiAttributeSet::GetMagicResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
		
		TagsToCaptureDefs.Add(FTangiGameplayTags::Attribute_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(FTangiGameplayTags::Attribute_Secondary_PhysicalResistance, PhysicalResistanceDef);
		TagsToCaptureDefs.Add(FTangiGameplayTags::Attribute_Secondary_MagicResistance, MagicResistanceDef);
	}
};

static const FTangiDamageStatics& DamageStatics()
{
	static FTangiDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float PhysicalDamage = 0.f;
	float MagicDamage = 0.f;
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FTangiGameplayTags::DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		checkf(FTangiDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false);
		if (DamageTypeValue <= 0.f) continue;
		
		if (DamageTypeTag.MatchesTag(FTangiGameplayTags::Damage_Physical))
		{
			PhysicalDamage += DamageTypeValue;
		}
		else if (DamageTypeTag.MatchesTag(FTangiGameplayTags::Damage_Magic))
		{
			MagicDamage += DamageTypeValue;
		}
	}
	
	float Damage = PhysicalDamage + MagicDamage;

#pragma region Critical Hit
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Clamp(SourceCriticalHitChance, 0.f, 100.f);
	const bool bIsCriticalHit = FMath::RandRange(1, 100) < SourceCriticalHitChance;
	UTangiAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	Damage *= bIsCriticalHit ? 1.25f : 1.f;
#pragma endregion
	
	// -----------------------------------------------------------------------------------------------------------------
	// Final damage being dealt
	// -----------------------------------------------------------------------------------------------------------------
	const FGameplayModifierEvaluatedData EvaluatedData(UTangiAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
