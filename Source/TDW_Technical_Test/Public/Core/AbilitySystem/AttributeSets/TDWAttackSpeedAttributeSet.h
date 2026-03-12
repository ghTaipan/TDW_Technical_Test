// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/AttributeSets/TDWAttributeSetBase.h"
#include "TDWAttackSpeedAttributeSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TDW_TECHNICAL_TEST_API UTDWAttackSpeedAttributeSet : public UTDWAttributeSetBase
{
	GENERATED_BODY()
	
public:
	
	UTDWAttackSpeedAttributeSet();
	
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Attribute Set")
	FGameplayAttributeData CurrentAttackSpeed;
	ATTRIBUTE_ACCESSORS(UTDWAttackSpeedAttributeSet, CurrentAttackSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Attribute Set")
	FGameplayAttributeData MaximumAttackSpeed;
	ATTRIBUTE_ACCESSORS(UTDWAttackSpeedAttributeSet, MaximumAttackSpeed)
};
