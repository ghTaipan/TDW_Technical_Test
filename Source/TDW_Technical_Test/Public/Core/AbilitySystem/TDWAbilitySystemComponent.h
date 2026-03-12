// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TDWAbilitySystemComponent.generated.h"

struct FTDWAbilitySystemInitializationSpec;

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeAbilitySystemData(const FTDWAbilitySystemInitializationSpec& InitializationData, AActor* InOwningActor, AActor* InAvatarActor);

	void AbilityInputPressed(const FGameplayTag& AbilityTag);
	void AbilityInputReleased(const FGameplayTag& AbilityTag);
};
