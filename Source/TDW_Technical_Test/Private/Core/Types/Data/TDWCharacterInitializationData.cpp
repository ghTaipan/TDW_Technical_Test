// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Types/Data/TDWCharacterInitializationData.h"

FTDWAbilitySystemInitializationSpec UTDWCharacterInitializationData::GetAbilitySystemInitializationData(
	const FGameplayTagContainer& CharacterTags) const
{
	return CharacterInitializationMap.FindRef(FTDWGameplayTagContainerMapKey(CharacterTags)).AbilitySystemInitializationData;
}

void UTDWCharacterInitializationData::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	
	const FName MemberPropertyName = PropertyChangedEvent.PropertyChain.GetActiveMemberNode()->GetValue()->GetFName();
	
	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(UTDWCharacterInitializationData, CharacterInitializationMap))
	{
		TMap<FTDWGameplayTagContainerMapKey, FTDWCharacterInitializationInfo> CleanMap;

		for (auto It = CharacterInitializationMap.CreateIterator(); It; ++It)
		{
			FTDWGameplayTagContainerMapKey Key = It.Key();
			const FTDWCharacterInitializationInfo Value = It.Value();

			Key.InvalidateHash();

			if (CleanMap.Contains(Key))
			{
				UE_LOG(LogTemp, Warning, TEXT("Removed duplicate Key in CharacterInitializationMap during edit."));
			}
			else
			{
				CleanMap.Add(Key, Value);
			}
		}
		
		CharacterInitializationMap = CleanMap;
	}
}
