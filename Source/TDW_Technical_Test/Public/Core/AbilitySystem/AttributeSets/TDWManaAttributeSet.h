// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/AttributeSets/TDWAttributeSetBase.h"
#include "TDWManaAttributeSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TDW_TECHNICAL_TEST_API UTDWManaAttributeSet : public UTDWAttributeSetBase
{
	GENERATED_BODY()
	
public:
	UTDWManaAttributeSet();

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Mana Attribute Set")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UTDWManaAttributeSet, CurrentMana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Mana Attribute Set")
	FGameplayAttributeData MaximumMana;
	ATTRIBUTE_ACCESSORS(UTDWManaAttributeSet, MaximumMana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Mana Attribute Set")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UTDWManaAttributeSet, ManaRegeneration)
};
