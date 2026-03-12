// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "TDWAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
