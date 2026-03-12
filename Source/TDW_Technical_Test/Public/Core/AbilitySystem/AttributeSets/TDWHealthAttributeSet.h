// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/AttributeSets/TDWAttributeSetBase.h"
#include "TDWHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TDW_TECHNICAL_TEST_API UTDWHealthAttributeSet : public UTDWAttributeSetBase
{
	GENERATED_BODY()
	
public:
	
	UTDWHealthAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UTDWHealthAttributeSet, Damage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Attribute Set")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UTDWHealthAttributeSet, CurrentHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Attribute Set")
	FGameplayAttributeData MaximumHealth;
	ATTRIBUTE_ACCESSORS(UTDWHealthAttributeSet, MaximumHealth)
};
