// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/TDWCharacterBase.h"
#include "TDWAICharacter.generated.h"

class UWidgetComponent;
class UTDWAttributeWidgetController;
/**
 * 
 */
UCLASS(Blueprintable)
class TDW_TECHNICAL_TEST_API ATDWAICharacter : public ATDWCharacterBase
{
	GENERATED_BODY()
	
public:
	ATDWAICharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void InitializeAbilitySystem(const FTDWAbilitySystemInitializationSpec& InitData) override;
	
	// Widget Protected Props
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Widgets")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComp;
	
private:
	void ShowHealthBarTagChanged(const FGameplayTag CallBackTag, int32 NewCount) const;
	void OnDeath(const FGameplayTag CallBackTag, int32 NewCount);
	
	UPROPERTY()
	TObjectPtr<UTDWAttributeWidgetController> EnemyWidgetController;
	UPROPERTY(EditAnywhere, Category = "Config|Widgets")
	TSubclassOf<UTDWAttributeWidgetController> EnemyWidgetControllerClass;
	
	FDelegateHandle ShowHealthBarTagChangedDelegateHandle;
};
