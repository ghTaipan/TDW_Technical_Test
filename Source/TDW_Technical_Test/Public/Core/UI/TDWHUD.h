// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDWHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FTDWWidgetControllerParams;
class UTDWAttributeWidgetController;
class UTDWUserWidget;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API ATDWHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitOverlay(UAbilitySystemComponent* ASC, const TArray<const UAttributeSet*>& AttributeSets);

private:
	UPROPERTY()
	TObjectPtr<UTDWUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UTDWUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTDWAttributeWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UTDWAttributeWidgetController> OverlayWidgetControllerClass;

public:
	UTDWAttributeWidgetController* GetOverlayWidgetController(const FTDWWidgetControllerParams& WCParams);
};
