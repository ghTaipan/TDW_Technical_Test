// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/TDWPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Core/AbilitySystem/TDWAbilitySystemComponent.h"
#include "Core/AbilitySystem/Types/Data/TDWAbilityInputData.h"
#include "Core/Game/TDWGameMode.h"
#include "Core/Library/TDWBlueprintFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LogTDWCharacter);

ATDWPlayerController::ATDWPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATDWPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATDWPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATDWPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATDWPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATDWPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MoveInputPressed);
		
		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATDWPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATDWPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATDWPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATDWPlayerController::OnTouchReleased);
		
		const ATDWGameMode* GM = UTDWBlueprintFunctionLibrary::GetGameMode(this);
		if (IsValid(GM))
		{
			for (const FTDWAbilityInputInfo& Info : GM->GetAbilityInputData()->GetAbilityInfoArray())
			{
				EnhancedInputComponent->BindAction(Info.InputAction, Info.InputPressedTriggerType, this, &ATDWPlayerController::AbilityInputPressed, Info.AbilityTag);
				EnhancedInputComponent->BindAction(Info.InputAction, Info.InputReleasedTriggerType, this, &ATDWPlayerController::AbilityInputReleased, Info.AbilityTag);
			}
		}
	}
	else
	{
		UE_LOG(LogTDWCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATDWPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATDWPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	// If we hit a surface, cache the location
	if (GetHitUnderCursor(Hit))
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATDWPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATDWPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATDWPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATDWPlayerController::MoveInputPressed(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	APawn* ControlledPawn = GetPawn();
	if (!(ControlledPawn->GetActorLocation() - CachedDestination).IsNearlyZero())
	{
		StopMovement();
	}
	
	// add movement 
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y); // forward
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X); // right
}

void ATDWPlayerController::AbilityInputPressed(FGameplayTag AbilityTag)
{
	PawnASC->AbilityInputPressed(AbilityTag);
}

void ATDWPlayerController::AbilityInputReleased(FGameplayTag AbilityTag)
{
	PawnASC->AbilityInputReleased(AbilityTag);
}

bool ATDWPlayerController::GetHitUnderCursor(FHitResult& Hit) const
{
	bool bHitSuccessful;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	}
	
	return bHitSuccessful;
}

void ATDWPlayerController::SetPawnASC(UTDWAbilitySystemComponent* ASC)
{
	PawnASC = MakeWeakObjectPtr(ASC);
}