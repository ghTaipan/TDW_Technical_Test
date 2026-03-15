// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/Widget/TDWUserWidget.h"
#include "Core/UI/WidgetController/TDWWidgetControllerBase.h" //  for weakptr

void UTDWUserWidget::SetWidgetController(UTDWWidgetControllerBase* InWidgetController)
{
	WidgetController = MakeWeakObjectPtr(InWidgetController);
	OnWidgetControllerSet();
}
