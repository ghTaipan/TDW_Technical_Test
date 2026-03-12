
// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Library/TDWBlueprintFunctionLibrary.h"

#include "ScalableFloat.h"
#include "Core/Game/TDWGameMode.h"
#include "Kismet/GameplayStatics.h"


ATDWGameMode* UTDWBlueprintFunctionLibrary::GetGameMode(const UObject* WorldContextObject)
{
	return Cast<ATDWGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

float UTDWBlueprintFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& ScalableFloat, float Level)
{
	if (ScalableFloat.IsValid())
	{
		return ScalableFloat.GetValueAtLevel(Level);
	}
	
	return 0.0f;
}
