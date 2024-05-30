// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/ExecCalc/ExecCalc_FallDamage.h"

#include "AbilitySystem/TangiAttributeSet.h"


void UExecCalc_FallDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float Damage = 0.f;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const float VelocityZ = Spec.GetLevel();
	if (VelocityZ <= -850.f)
	{
		// VelocityZ: -1000 () =>    4.2dmg
		// VelocityZ: -3000 () =>   65.4dmg
		// VelocityZ: -6000 () =>  369.7dmg
		// VelocityZ: -9000 () => 1018.8dmg
		Damage += FMath::Pow(VelocityZ / 200.0f * -1, 2.5f) * 0.075f;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "VelocityZ: " + FString::SanitizeFloat(VelocityZ) + "\nDamage: " + FString::SanitizeFloat(Damage));
	const FGameplayModifierEvaluatedData EvaluatedData(UTangiAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

