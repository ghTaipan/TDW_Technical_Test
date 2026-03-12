// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TDWAssetManager.h"

#include "AbilitySystemGlobals.h"

UTDWAssetManager& UTDWAssetManager::Get()
{
	check(GEngine);
	return *Cast<UTDWAssetManager>(GEngine->AssetManager);
}

void UTDWAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UAbilitySystemGlobals::Get().InitGlobalData();
}
