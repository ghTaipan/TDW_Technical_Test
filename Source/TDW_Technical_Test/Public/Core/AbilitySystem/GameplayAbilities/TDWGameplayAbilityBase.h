// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Core/AbilitySystem/Types/TDWDamageTypes.h"
#include "TDWGameplayAbilityBase.generated.h"

class UTDWAbilitySystemComponent;
class ATDWCharacterBase;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UTDWGameplayAbilityBase();
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetMontageToPlay(UAnimMontage* InMontage);
	
	UFUNCTION(BlueprintCallable, BlueprintPure = "false")
	FGameplayEffectContextHandle ApplyDamageEffectFromSpec(const FGameplayEffectContextHandle& EffectContext) const;
	
	TWeakObjectPtr<ATDWCharacterBase> BaseCharacter;
	TWeakObjectPtr<UTDWAbilitySystemComponent> ASC;
	TWeakObjectPtr<UAnimMontage> MontageToPlay;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Damage")
	FTDWDamageSpec DefaultDamageSpec;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ATDWCharacterBase* GetBaseCharacter() const {return BaseCharacter.Get();}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTDWAbilitySystemComponent* GetASC() const {return ASC.Get();}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAnimMontage* GetMontageToPlay() const {return MontageToPlay.Get();}
};
