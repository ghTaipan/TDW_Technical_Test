// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDWBlueprintFunctionLibrary.generated.h"

struct FScalableFloat;
class ATDWGameMode;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FCFunctionLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static ATDWGameMode* GetGameMode(const UObject* WorldContextObject);
	
	template <typename T>
	static UClass* LoadAndReturnSoftClass(TSoftClassPtr<T>& SoftClass);
	
	UFUNCTION(BlueprintCallable, Category="FCFunctionLibrary")
	static float GetScalableFloatValueAtLevel(const FScalableFloat& ScalableFloat, float Level);
};

template <typename T>
UClass* UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(TSoftClassPtr<T>& SoftClass)
{
	UClass* ClassToReturn = nullptr;
	
	if (!SoftClass.IsNull())
	{
		ClassToReturn = SoftClass.Get();

		if (!IsValid(ClassToReturn))
		{
			ClassToReturn = SoftClass.LoadSynchronous();
		}
	}

	return ClassToReturn;
}