// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TDWAbilityInputData.generated.h"

class UInputAction;

UENUM(BlueprintType)
enum class ETDWAbilityInput: uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Press = 1 UMETA(DisplayName = "Press"),
	Held = 2  UMETA(DisplayName = "Held"),
	Release = 3  UMETA(DisplayName = "Release")
};

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
	ETDWAbilityInput InputPressedTriggerType = ETDWAbilityInput::None;

	// What Input Action trigger type to listen to for input released events.
	UPROPERTY(EditAnywhere)
	ETDWAbilityInput InputReleasedTriggerType = ETDWAbilityInput::None;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer TagsRequiredToBind;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer TagsToBlockBind;
	
	uint32 PressedInputBindingHandle = 0;
	uint32 ReleasedInputBindingHandle = 0;

	bool bBound = false;
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
