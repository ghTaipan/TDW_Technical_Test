// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/TDWHUD.h"

#include "AbilitySystemComponent.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"
#include "Core/UI/Widget/TDWUserWidget.h"
#include "Core/UI/WidgetController/TDWAttributeWidgetController.h"
#include "Core/UI/WidgetController/TDWWidgetControllerBase.h"

void ATDWHUD::InitOverlay(UAbilitySystemComponent* ASC, const TArray<const UAttributeSet*>& AttributeSets)
{
	UClass* WCClass = UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(OverlayWidgetClass);
	if (IsValid(WCClass) && IsValid(ASC) && !AttributeSets.IsEmpty())
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WCClass);
		UTDWUserWidget* TDWWidget = Cast<UTDWUserWidget>(Widget);
		if (IsValid(TDWWidget))
		{
			UTDWAttributeWidgetController* TempController = GetOverlayWidgetController(FTDWWidgetControllerParams(ASC, AttributeSets));
			if (IsValid(TempController))
			{
				TDWWidget->SetWidgetController(TempController);
				TempController->BroadCastInitialValues();

				TDWWidget->AddToViewport();
			}
		}
	}
}

UTDWAttributeWidgetController* ATDWHUD::GetOverlayWidgetController(const FTDWWidgetControllerParams& WCParams)
{
	if (!IsValid(OverlayWidgetController))
	{
		const TSubclassOf<UTDWAttributeWidgetController> WCClass = UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(OverlayWidgetControllerClass);
		if (IsValid(WCClass))
		{
			OverlayWidgetController = NewObject<UTDWAttributeWidgetController>(this, WCClass);
			OverlayWidgetController->SetWidgetControllerParams(WCParams);
			OverlayWidgetController->BindCallbacksToDependencies();
		}
	}
	
	return OverlayWidgetController;
}
