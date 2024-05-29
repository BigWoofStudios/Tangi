// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/ExecCalc/ExecCalc_FallDamage.h"

#include "AbilitySystem/TangiAttributeSet.h"


void UExecCalc_FallDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float Damage = 0.f;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	if (float EffectLevel = Spec.GetLevel(); EffectLevel <= -1000.f)
	{
		EffectLevel *= -1;
		Damage += FMath::Pow(EffectLevel / 50.f, FMath::Max(1.f, EffectLevel / 3000));
	}
	
	const FGameplayModifierEvaluatedData EvaluatedData(UTangiAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

