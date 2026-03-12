#pragma once

#include "GameplayTagContainer.h"
#include "TDWAttributeTypes.generated.h"

USTRUCT(BlueprintType)
struct FTDWAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription= FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

USTRUCT(BlueprintType)
struct FTDWAttributeSpec
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FTDWAttributeInfo AttributeInfo;
	
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};