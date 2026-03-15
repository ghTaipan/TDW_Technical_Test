// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/TDWAbilitySystemBlueprintLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Core/TDWGameplayTags.h"
#include "Core/AbilitySystem/Types/TDWAbilityTypes.h"
#include "Core/AbilitySystem/Types/TDWDamageTypes.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"

FGameplayEffectContextHandle UTDWAbilitySystemBlueprintLibrary::ApplyDamageEffect(const FTDWDamageSpec& DamageSpecifier, const FGameplayEffectContextHandle& DamageEffectContext)
{
	AActor* SourceAvatarActor = DamageSpecifier.DamageApplier.Get();
	const UAbilitySystemComponent* SourceAbilitySystemComponent = GetAbilitySystemComponent(SourceAvatarActor);
	
	// Make Effect Context
	FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	EffectContextHandle.AddHitResult(*DamageEffectContext.GetHitResult(), true);
	SetDamageSpec(EffectContextHandle, DamageSpecifier);
	
	TSoftClassPtr<UGameplayEffect> DamageEffectClass = DamageSpecifier.DamageEffectClass;
	const TSubclassOf<UGameplayEffect>& EffectClass =  UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(DamageEffectClass);
	if (!ensure(::IsValid(EffectClass)))
	{
		return FGameplayEffectContextHandle();
	}
	
	// Make Spec
	const FGameplayEffectSpecHandle& SpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(EffectClass, DamageSpecifier.DamageLevel,EffectContextHandle);
	if (!ensure(SpecHandle.IsValid() && SpecHandle.Data.IsValid()))
	{
		return FGameplayEffectContextHandle();
	}
	
	// Assign Damage values
	if (ensure(!DamageSpecifier.DamageTypesToDamages.IsEmpty()))
	{
		for (const FGameplayTag& DamageType : NativeGameplayTags::DamageType::GetDamageTypeTags())
		{
			const FScalableFloat& ScalableDamage = DamageSpecifier.DamageTypesToDamages.FindRef(DamageType);
			if (!ScalableDamage.IsValid())
			{
				continue;
			}
			
			const float Damage = UTDWBlueprintFunctionLibrary::GetScalableFloatValueAtLevel(ScalableDamage, DamageSpecifier.DamageLevel);
			AssignTagSetByCallerMagnitude(SpecHandle, DamageType, Damage);
		}
	}
	
	// Apply Damage
	UAbilitySystemComponent* TargetAbilitySystemComponent = GetAbilitySystemComponent( DamageSpecifier.DamageReceiver.Get());
	if (::IsValid(TargetAbilitySystemComponent))
	{
		TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	return {};
}

FTDWDamageSpec UTDWAbilitySystemBlueprintLibrary::GetDamageSpec(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FTDWGameplayEffectContext* TDWEffectContext = static_cast<const FTDWGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return TDWEffectContext->GetDamageSpec();
	}
	
	return FTDWDamageSpec();
}

void UTDWAbilitySystemBlueprintLibrary::SetDamageSpec(FGameplayEffectContextHandle& EffectContextHandle,
                                                      const FTDWDamageSpec& DamageSpec)
{
	if (FTDWGameplayEffectContext* TDWEffectContext = static_cast<FTDWGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return TDWEffectContext->SetDamageSpec(DamageSpec);
	}
}