// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDWUserWidget.generated.h"

class UTDWWidgetControllerBase;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UTDWWidgetControllerBase* InWidgetController);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
	
private:
	UPROPERTY()
	TWeakObjectPtr<UTDWWidgetControllerBase> WidgetController;

public:
	UFUNCTION(BlueprintCallable)
	UTDWWidgetControllerBase* GetWidgetController() const {return WidgetController.Get();}
};
