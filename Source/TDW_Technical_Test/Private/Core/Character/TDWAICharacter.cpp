// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/TDWAICharacter.h"

#include "Components/WidgetComponent.h"
#include "Core/TDWGameplayTags.h"
#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/Game/TDWGameMode.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"
#include "Core/Types/Data/TDWCharacterInitializationData.h"
#include "Core/UI/Widget/TDWUserWidget.h"
#include "Core/UI/WidgetController/TDWAttributeWidgetController.h"

ATDWAICharacter::ATDWAICharacter()
{
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	HealthBarWidgetComp->SetupAttachment(GetMesh());
}

void ATDWAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	const ATDWGameMode* GM = UTDWBlueprintFunctionLibrary::GetGameMode(this);
	if (IsValid(GM))
	{
		const UTDWCharacterInitializationData* CharData = GM->GetCharacterInitializationData();
		if (IsValid(CharData))
		{
			HealthBarWidgetComp->SetVisibility(false);
			UTDWUserWidget* HealthBarWidget = Cast<UTDWUserWidget>(HealthBarWidgetComp->GetWidget());
            
			UClass* WCClass = UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(EnemyWidgetControllerClass);
			if (IsValid(HealthBarWidget) && IsValid(WCClass))
			{
				EnemyWidgetController = NewObject<UTDWAttributeWidgetController>(this, WCClass);
				FTDWWidgetControllerParams WcParams;
            	
				for (TSoftClassPtr<UAttributeSet> Elem : CharData->GetAbilitySystemInitializationData(CharacterSpecTags).AttributeSets)
				{
					const UAttributeSet* AS = AbilitySystemComponent->GetAttributeSet(UTDWBlueprintFunctionLibrary::LoadAndReturnSoftClass(Elem));
					if (IsValid(AS))
					{
						WcParams.AttributeSets.Add(AS);
					}
				}
            	
				WcParams.AbilitySystemComponent = AbilitySystemComponent;
				EnemyWidgetController->SetWidgetControllerParams(WcParams);
				EnemyWidgetController->BindCallbacksToDependencies();
				HealthBarWidget->SetWidgetController(EnemyWidgetController);
				EnemyWidgetController->BroadCastInitialValues();
			}
		}
	}
}

void ATDWAICharacter::InitializeAbilitySystem(const FTDWAbilitySystemInitializationSpec& InitData)
{
	Super::InitializeAbilitySystem(InitData);
	
	ShowHealthBarTagChangedDelegateHandle = AbilitySystemComponent->RegisterGameplayTagEvent(NativeGameplayTags::Effect::Combat::TAG_Effect_Combat_Show_Health_Bar,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::ShowHealthBarTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(NativeGameplayTags::Ability::CharacterState::TAG_Ability_Character_State_Death,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnDeath);
}

void ATDWAICharacter::ShowHealthBarTagChanged(const FGameplayTag CallBackTag, int32 NewCount) const
{
	HealthBarWidgetComp->SetVisibility(NewCount > 0);
}

void ATDWAICharacter::OnDeath(const FGameplayTag CallBackTag, int32 NewCount)
{
	HealthBarWidgetComp->SetVisibility(false);
	AbilitySystemComponent->RegisterGameplayTagEvent(NativeGameplayTags::Effect::Combat::TAG_Effect_Combat_Show_Health_Bar,
		EGameplayTagEventType::NewOrRemoved).Remove(ShowHealthBarTagChangedDelegateHandle);
}
