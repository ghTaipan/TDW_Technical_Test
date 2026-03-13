// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Types/TDWDamageTypes.h"
#include "TDWAbilitySystemBlueprintLibrary.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAbilitySystemBlueprintLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="TDWAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FTDWDamageSpec& DamageSpecifier, 
		const FGameplayEffectContextHandle& DamageEffectContext);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="TDWAbilitySystemLibrary|GameplayEffectContext")
	static FTDWDamageSpec GetDamageSpec(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="TDWAbilitySystemLibrary|GameplayEffectContext")
	static void SetDamageSpec(FGameplayEffectContextHandle& EffectContextHandle, const FTDWDamageSpec& DamageSpec);
};
