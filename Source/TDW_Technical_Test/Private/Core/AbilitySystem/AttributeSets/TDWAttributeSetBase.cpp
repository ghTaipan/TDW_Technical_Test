// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/AttributeSets/TDWAttributeSetBase.h"

void UTDWAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttributes(Attribute, NewValue);
}

void UTDWAttributeSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttributes(Attribute, NewValue);
}

void UTDWAttributeSetBase::AdjustAttributeForMaxChange(const FGameplayAttribute& AffectedAttribute,
	float OldMaxValue, float NewMaxValue, bool bUpdateByPercentage) const
{
	UAbilitySystemComponent* const ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	if (bUpdateByPercentage)
	{
		ASC->SetNumericAttributeBase(AffectedAttribute, ASC->GetNumericAttributeBase(AffectedAttribute) * NewMaxValue / OldMaxValue);
	}

	else if (NewMaxValue <= OldMaxValue + UE_SMALL_NUMBER)
	{
		ASC->SetNumericAttributeBase(AffectedAttribute, NewMaxValue);
	}
}

void UTDWAttributeSetBase::CheckMaxReachedForAttribute(const FGameplayAttributeData& MaxAttribute,
	const FGameplayTag& MaxTag, const float& NewValue) const
{

	UAbilitySystemComponent* const ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const float Max = MaxAttribute.GetCurrentValue();
	const bool bHasTag = ASC->HasMatchingGameplayTag(MaxTag);

	int32 Count = -1;

	if (NewValue >= Max && !bHasTag)
	{
		Count = 1;
	}
	else if (NewValue < Max && bHasTag)
	{
		Count = 0;
	}

	if (Count >= 0)
	{
		ASC->SetLooseGameplayTagCount(MaxTag, Count);
	}
}

void UTDWAttributeSetBase::CheckMinReachedForAttribute(const FGameplayTag& MinTag, const float& NewValue) const
{
	UAbilitySystemComponent* const ASC = GetOwningAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}
	
	const bool bHasTag = ASC->HasMatchingGameplayTag(MinTag);

	int32 Count = -1;

	if (NewValue <= 0.0f && !bHasTag)
	{
		Count = 1;
	}
	else if (NewValue > 0.0f && bHasTag)
	{
		Count = 0;
	}

	if (Count >= 0)
	{
		ASC->SetLooseGameplayTagCount(MinTag, Count);
	}
}
