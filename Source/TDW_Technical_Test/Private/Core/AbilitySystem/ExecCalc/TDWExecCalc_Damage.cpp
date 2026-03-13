// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/ExecCalc/TDWExecCalc_Damage.h"

#include "Core/TDWGameplayTags.h"
#include "Core/AbilitySystem/AttributeSets/TDWHealthAttributeSet.h"

void UTDWExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Iterating over each damage type to check if a value which is bigger than 0 assigned to tag.
	float  Damage = 0.0f;
	for (const FGameplayTag& DamageTypeTag : NativeGameplayTags::DamageType::GetDamageTypeTags())
	{
		const float DamageTypeValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(DamageTypeTag, false);
		if (DamageTypeValue > UE_SMALL_NUMBER)
		{
			Damage += DamageTypeValue;
		}
	}
	
	const FGameplayModifierEvaluatedData EvaluatedDamageData(UTDWHealthAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedDamageData);
}
