// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/TDWPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/Player/TDWPlayerController.h"
#include "GameFramework/SpringArmComponent.h"

ATDWPlayerCharacter::ATDWPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ATDWPlayerCharacter::PostInitializeAbilitySystem_Implementation()
{
	Super::PostInitializeAbilitySystem_Implementation();
	
	ATDWPlayerController* PC = Cast<ATDWPlayerController>(Controller);
	if (IsValid(PC))
	{
		PC->SetPawnASC(Cast<UTDWAbilitySystemComponent>(AbilitySystemComponent));
	}
}
