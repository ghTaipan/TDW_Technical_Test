	// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"

#include "Core/TDWGameplayTags.h"
#include "Core/AbilitySystem/GameplayAbilities/TDWGameplayAbilityBase.h"
#include "Core/AbilitySystem/Types/TDWAbilityTypes.h"

void UTDWAbilitySystemComponent::InitializeAbilitySystemData(
	const FTDWAbilitySystemInitializationSpec& InitializationData, AActor* InOwningActor, AActor* InAvatarActor)
{
	
	InitAbilityActorInfo(InOwningActor, InAvatarActor);
	
	if (!InitializationData.GameplayTags.IsEmpty())
	{
		AddLooseGameplayTags(InitializationData.GameplayTags);
	}

	// Grant Attribute Sets
	if (!InitializationData.AttributeSets.IsEmpty())
	{
		for (const TSubclassOf<UAttributeSet>& AttributeSetClass : InitializationData.AttributeSets)
		{
			GetOrCreateAttributeSubobject(AttributeSetClass);
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
		for (const TSubclassOf<UGameplayAbility>& GameplayAbility : InitializationData.GameplayAbilities)
		{
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
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : InitializationData.GameplayEffects)
		{
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