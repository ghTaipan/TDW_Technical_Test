// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/Types/TDWAbilityTypes.h"
#include "Core/Types/TDWTypes.h"
#include "Engine/DataAsset.h"
#include "TDWCharacterInitializationData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTDWCharacterInitializationInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System", Meta = (ShowOnlyInnerProperties))
	FTDWAbilitySystemInitializationSpec AbilitySystemInitializationData;
};

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWCharacterInitializationData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FTDWAbilitySystemInitializationSpec GetAbilitySystemInitializationData(const FGameplayTagContainer& CharacterTags) const;
	
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
private:
	// Tags To Enter Type (If Player, then the Rest is not needed), Family, Class, Rank
	UPROPERTY(EditDefaultsOnly)
	TMap<FTDWGameplayTagContainerMapKey, FTDWCharacterInitializationInfo> CharacterInitializationMap;
};
