	// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"

#include "Core/TDWGameplayTags.h"
#include "Core/AbilitySystem/GameplayAbilities/TDWGameplayAbilityBase.h"
#include "Core/AbilitySystem/Types/TDWAbilityTypes.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"

void UTDWAbilitySystemComponent::InitializeAbilitySystemData(
	const FTDWAbilitySystemInitializationSpec& InitializationData, AActor* InOwningActor, AActor* InAvatarActor)
{
	if (bAbilitySystemInitialized)
	{
		return;
	}
	
	bAbilitySystemInitialized = true;
	
	InitAbilityActorInfo(InOwningActor, InAvatarActor);
	
	if (!InitializationData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(InitializationData.GameplayTags);
	}

	// Grant Attribute Sets
	if (!InitializationData.AttributeSets.IsEmpty())
	{
		for (TSoftClassPtr<UAttributeSet> SoftAttributeSetClass : InitializationData.AttributeSets)
		{
			GetOrCreateAttributeSubobject(UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(SoftAttributeSetClass));
		}
	}

	// Set base attributes.
	if (!InitializationData.AttributeBaseValues.IsEmpty())
	{
		for (const TTuple<FGameplayAttribute, FTDWAttributeInitializer>& AttributeBaseValue : InitializationData.AttributeBaseValues)
		{
			if (HasAttributeSetForAttribute(AttributeBaseValue.Key))
			{
				SetNumericAttributeBase(AttributeBaseValue.Key, AttributeBaseValue.Value.Value.GetValueAtLevel(0.f));
			}
		}
	}

	// Grant Gameplay Abilities
	if (!InitializationData.GameplayAbilities.IsEmpty())
	{
		for (TSoftClassPtr<UGameplayAbility> SoftGameplayAbilityClass : InitializationData.GameplayAbilities)
		{
			UClass* GameplayAbilityClass = UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(SoftGameplayAbilityClass);
			if (!IsValid(GameplayAbilityClass))
			{
				continue;
			}
			
			UGameplayAbility* GameplayAbility = Cast<UGameplayAbility>(GameplayAbilityClass->GetDefaultObject());
			if (!IsValid(GameplayAbility))
			{
				continue;
			}
			
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbility, 0, INDEX_NONE, this);
			UTDWGameplayAbilityBase* TDWAbility = Cast<UTDWGameplayAbilityBase>(AbilitySpec.Ability);
		
			if (IsValid(TDWAbility))
			{
				const FGameplayTagContainer& AssetTags = TDWAbility->GetAssetTags();
				AbilitySpec.GetDynamicSpecSourceTags().AppendTags(AssetTags);
			}
		
			GiveAbility(AbilitySpec);
		}
	}

	// Apply Gameplay Effects
	if (!InitializationData.GameplayEffects.IsEmpty())
	{
		for (TSoftClassPtr<UGameplayEffect> SoftGameplayEffect : InitializationData.GameplayEffects)
		{
			TSubclassOf<UGameplayEffect> GameplayEffect = UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(SoftGameplayEffect);
			if (!IsValid(GameplayEffect))
			{
				continue;
			}
			
			FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);

			if (FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingSpec(GameplayEffect, 1, EffectContextHandle); GameplayEffectSpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), this);
			}
		}
	}
}

void UTDWAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& AbilityTag)
{
	if (!AbilityTag.IsValid())
	{
		return;
	}
	
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		const FGameplayTagContainer TempAbilityTags = AbilitySpec.GetDynamicSpecSourceTags();
		if (!TempAbilityTags.HasTagExact(AbilityTag))
		{
			continue;
		}
		
		if (AbilitySpec.IsActive())
		{
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle,
	AbilitySpec.GetPrimaryInstance()->GetCurrentActivationInfo().GetActivationPredictionKey());
			AbilitySpecInputPressed(AbilitySpec);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UTDWAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& AbilityTag)
{
	if (!AbilityTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(AbilityTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle,
				AbilitySpec.GetPrimaryInstance()->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
	}
}