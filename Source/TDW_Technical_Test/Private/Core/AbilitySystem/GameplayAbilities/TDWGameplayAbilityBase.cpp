// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/GameplayAbilities/TDWGameplayAbilityBase.h"

#include "Core/AbilitySystem/TDWAbilitySystemBlueprintLibrary.h"
#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/Character/TDWCharacterBase.h"

UTDWGameplayAbilityBase::UTDWGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTDWGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	MontageToPlay = nullptr;
}

void UTDWGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	BaseCharacter = MakeWeakObjectPtr(Cast<ATDWCharacterBase>(ActorInfo->AvatarActor));
	ASC = MakeWeakObjectPtr(Cast<UTDWAbilitySystemComponent>(ActorInfo->AbilitySystemComponent));
	
	DefaultDamageSpec.DamageLevel = GetAbilityLevel();
}

void UTDWGameplayAbilityBase::SetMontageToPlay_Implementation(UAnimMontage* InMontage)
{
	MontageToPlay = MakeWeakObjectPtr(InMontage);
}

FGameplayEffectContextHandle UTDWGameplayAbilityBase::ApplyDamageEffectFromSpec(const FGameplayEffectContextHandle& EffectContext) const
{
	FTDWDamageSpec TempDamageSpec = DefaultDamageSpec;
	TempDamageSpec.DamageApplier = BaseCharacter;
	if (const FHitResult* Hit = EffectContext.GetHitResult())
	{
		TempDamageSpec.DamageReceiver = MakeWeakObjectPtr(Hit->GetActor());
	}
	
	return UTDWAbilitySystemBlueprintLibrary::ApplyDamageEffect(TempDamageSpec, EffectContext);
}
