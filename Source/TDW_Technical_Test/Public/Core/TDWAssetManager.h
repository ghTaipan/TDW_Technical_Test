// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TDWAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UTDWAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	
};
