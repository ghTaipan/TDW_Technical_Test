// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/TDWAbilitySystemGlobals.h"
#include "Core/AbilitySystem/Types/TDWAbilityTypes.h"

FGameplayEffectContext* UTDWAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FTDWGameplayEffectContext();
}
