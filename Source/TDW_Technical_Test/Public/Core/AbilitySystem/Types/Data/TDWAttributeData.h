// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/Types/TDWAttributeTypes.h"
#include "Engine/DataAsset.h"
#include "TDWAttributeData.generated.h"

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAttributeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FTDWAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FTDWAttributeInfo> AttributeInformation;
	
};
