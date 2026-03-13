// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/AbilitySystem/AttributeSets/TDWHealthAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Core/TDWGameplayTags.h"

namespace CharacterState = NativeGameplayTags::Ability::CharacterState;
namespace Attribute = NativeGameplayTags::Attribute;

UTDWHealthAttributeSet::UTDWHealthAttributeSet()
{
	TagsToAttributes.Add(Attribute::Current::TAG_Attribute_Current_Health, GetCurrentHealthAttribute());
	TagsToAttributes.Add(Attribute::Max::TAG_Attribute_Max_Health, GetMaximumHealthAttribute());
}

void UTDWHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the Health change and then clamp it.
			const float NewHealth = FMath::Clamp(GetCurrentHealth() - LocalDamageDone, 0.0f, GetMaximumHealth());
			
			SetCurrentHealth(NewHealth);
			
			if (NewHealth > 0.0f)
			{
				Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(CharacterState::TAG_Ability_Character_State_Hit_React));
			}
			else
			{
				Data.Target.TryActivateAbilitiesByTag(FGameplayTagContainer(CharacterState::TAG_Ability_Character_State_Death));
			}
			
			FGameplayEventData Payload;
			Payload.ContextHandle  = Data.EffectSpec.GetContext();
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.AbilityActorInfo->AvatarActor.Get(),
				NativeGameplayTags::Event::Combat::TAG_Event_Combat_Hit_React, Payload);
		}
	}
}

void UTDWHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaximumHealthAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentHealthAttribute(), OldValue, NewValue, false);
	}
}

void UTDWHealthAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetMaximumHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumHealth());
	}
}
