
#include "Core/UI/WidgetController/TDWAttributeWidgetController.h"

#include "Core/AbilitySystem/AttributeSets/TDWAttributeSetBase.h"
#include "Core/AbilitySystem/Types/Data/TDWAttributeData.h"

void UTDWAttributeWidgetController::BroadCastInitialValues()
{
	ensure(IsValid(AttributeData));
	
	for (const UAttributeSet* AS : GetAttributeSets())
	{
		const UTDWAttributeSetBase* TDWASC = Cast<UTDWAttributeSetBase>(AS);
		if (!IsValid(TDWASC))
		{
			return;
		}
		for (const auto& Pair : TDWASC->GetTagsToAttributes())
		{
			BroadCastAttributeInfo(Pair.Key, Pair.Value);
		}
	}
}

void UTDWAttributeWidgetController::BindCallbacksToDependencies()
{
	for (const UAttributeSet* AS : GetAttributeSets())
	{
		const UTDWAttributeSetBase* TDWAS = Cast<UTDWAttributeSetBase>(AS);
		if (!IsValid(TDWAS))
		{
			return;
		}
		for (const auto& Pair : TDWAS->GetTagsToAttributes())
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddWeakLambda(this, 
				[this, Pair](const FOnAttributeChangeData& Data)
				{
					BroadCastAttributeInfo(Pair.Key, Pair.Value);
				}
			);
		}
	}
}

void UTDWAttributeWidgetController::BroadCastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute) const
{
	const FTDWAttributeSpec Spec = FTDWAttributeSpec(AttributeData->FindAttributeInfoForTag(AttributeTag),
		AbilitySystemComponent->GetNumericAttribute(Attribute));
	
	AttributeInfoDelegate.Broadcast(Spec);
}