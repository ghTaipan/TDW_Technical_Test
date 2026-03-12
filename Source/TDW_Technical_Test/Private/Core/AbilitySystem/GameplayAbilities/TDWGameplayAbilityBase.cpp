// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/GameplayAbilities/TDWGameplayAbilityBase.h"

#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/Character/TDWCharacterBase.h"

UTDWGameplayAbilityBase::UTDWGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTDWGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	BaseCharacter = Cast<ATDWCharacterBase>(ActorInfo->AvatarActor);
	ASC = Cast<UTDWAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
}