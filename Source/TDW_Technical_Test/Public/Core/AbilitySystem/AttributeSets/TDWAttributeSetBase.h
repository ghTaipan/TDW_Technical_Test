// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // for child includes

#include "TDWAttributeSetBase.generated.h"

// used for creating necessary attribute functions with 1 macro
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class TDW_TECHNICAL_TEST_API UTDWAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const {};
	
	// Used for adjusting the fundamental version of the value, when there is a change of max version of it happens.
	void AdjustAttributeForMaxChange(const FGameplayAttribute& AffectedAttribute, float OldMaxValue, float NewMaxValue, bool bUpdateByPercentage) const;
	// Used for checking if an attribute reached its max; if so, add a tag (so that a Gameplay Effect can end itself).
	void CheckMaxReachedForAttribute(const FGameplayAttributeData& MaxAttribute, const FGameplayTag& MaxTag, const float& NewValue) const;
	// Used for checking if an attribute reached its min; if so, add a tag (so that a Gameplay Effect can end itself).
	void CheckMinReachedForAttribute(const FGameplayTag& MinTag, const float& NewValue) const;

	UPROPERTY()
	TMap<FGameplayTag, FGameplayAttribute> TagsToAttributes;
	
public:
	UFUNCTION(BlueprintCallable)
	TMap<FGameplayTag, FGameplayAttribute> GetTagsToAttributes() const {return TagsToAttributes;}
};
