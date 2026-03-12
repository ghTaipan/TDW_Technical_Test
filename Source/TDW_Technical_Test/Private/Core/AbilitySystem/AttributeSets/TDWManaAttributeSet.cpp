// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/AttributeSets/TDWManaAttributeSet.h"

#include "Core/TDWGameplayTags.h"

namespace Attribute = NativeGameplayTags::Attribute;

UTDWManaAttributeSet::UTDWManaAttributeSet()
{
	TagsToAttributes.Add(Attribute::Max::TAG_Attribute_Max_Mana, GetMaximumManaAttribute());
	TagsToAttributes.Add(Attribute::Current::TAG_Attribute_Current_Mana, GetCurrentManaAttribute());
	TagsToAttributes.Add(Attribute::Regeneration::TAG_Attribute_Regeneration_Mana, GetManaRegenerationAttribute());
}

void UTDWManaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentManaAttribute())
	{
		CheckMaxReachedForAttribute(GetMaximumMana(), Attribute::State::TAG_State_Max_Mana.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetMaximumManaAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentManaAttribute(), OldValue, NewValue, false);
	}
}

void UTDWManaAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetMaximumManaAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
		return;
	}
	
	if (Attribute == GetCurrentManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumMana());
		return;
	}
	
	if (Attribute == GetManaRegenerationAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
}
