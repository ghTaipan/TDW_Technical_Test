// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/TDWCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/Game/TDWGameMode.h"
#include "Core/Types/Data/TDWCharacterInitializationData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"

ATDWCharacterBase::ATDWCharacterBase()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Configure character movement
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	CharMovement->bOrientRotationToMovement = true; // Rotate character to moving direction
	CharMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	CharMovement->bConstrainToPlane = true;
	CharMovement->bSnapToPlaneAtStart = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTDWAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PrimaryActorTick.bCanEverTick = false;
}

void ATDWCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	const ATDWGameMode* GM = UTDWBlueprintFunctionLibrary::GetGameMode(this);
	if (IsValid(GM))
	{
		const UTDWCharacterInitializationData* CharData = GM->GetCharacterInitializationData();
		if (IsValid(CharData))
		{
			InitializeAbilitySystem(CharData->GetAbilitySystemInitializationData(CharacterSpecTags));
		}
	}
	
	PostInitializeAbilitySystem();
}

void ATDWCharacterBase::InitializeAbilitySystem(const FTDWAbilitySystemInitializationSpec& InitData)
{
	AbilitySystemComponent->InitializeAbilitySystemData(InitData, this, this);
}

void ATDWCharacterBase::PostInitializeAbilitySystem_Implementation()
{}

UAbilitySystemComponent* ATDWCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}