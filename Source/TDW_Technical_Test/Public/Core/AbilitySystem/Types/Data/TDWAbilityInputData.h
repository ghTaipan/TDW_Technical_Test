// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputTriggers.h"

#include "TDWAbilityInputData.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTDWAbilityInputInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;
	
	// What Input Action trigger type to listen to for input pressed events.
	UPROPERTY(EditAnywhere)
	ETriggerEvent InputPressedTriggerType = ETriggerEvent::None;

	// What Input Action trigger type to listen to for input released events.
	UPROPERTY(EditAnywhere)
	ETriggerEvent InputReleasedTriggerType = ETriggerEvent::None;
};

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAbilityInputData : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTDWAbilityInputInfo> AbilityInputInfoArray;
	
public:
	const TArray<FTDWAbilityInputInfo>& GetAbilityInfoArray() const {return AbilityInputInfoArray;}
};
