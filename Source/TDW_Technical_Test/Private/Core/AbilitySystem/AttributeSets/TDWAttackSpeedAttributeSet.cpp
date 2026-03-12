// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/AttributeSets/TDWAttackSpeedAttributeSet.h"

#include "Core/TDWGameplayTags.h"

namespace Attribute = NativeGameplayTags::Attribute;

UTDWAttackSpeedAttributeSet::UTDWAttackSpeedAttributeSet()
{
	TagsToAttributes.Add(Attribute::Max::TAG_Attribute_Max_Attack_Speed, GetMaximumAttackSpeedAttribute());
	TagsToAttributes.Add(Attribute::Current::TAG_Attribute_Current_Attack_Speed, GetCurrentAttackSpeedAttribute());
}

void UTDWAttackSpeedAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetMaximumAttackSpeedAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentAttackSpeedAttribute(), OldValue, NewValue, false);
	}
}

void UTDWAttackSpeedAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetCurrentAttackSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumAttackSpeed());
		return;
	}
	
	if (Attribute == GetMaximumAttackSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
