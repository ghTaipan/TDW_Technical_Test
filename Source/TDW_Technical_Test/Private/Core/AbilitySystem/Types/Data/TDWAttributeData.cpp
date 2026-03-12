// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AbilitySystem/Types/Data/TDWAttributeData.h"

FTDWAttributeInfo UTDWAttributeData::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FTDWAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find Info for AttributeTag [%s] on AttributeInfo [%s]."),*AttributeTag.ToString() , *GetNameSafe(this));
	}
	return  FTDWAttributeInfo();
}
