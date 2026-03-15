#include "Core/UI/WidgetController/TDWWidgetControllerBase.h"

void UTDWWidgetControllerBase::SetWidgetControllerParams(const FTDWWidgetControllerParams& WCParams)
{
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSets;
}

void UTDWWidgetControllerBase::BroadCastInitialValues(){}

void UTDWWidgetControllerBase::BindCallbacksToDependencies(){}