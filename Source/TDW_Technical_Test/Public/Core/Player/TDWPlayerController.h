// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TDWPlayerController.generated.h"

struct FTDWAbilityInputInfo;
enum class ETDWAbilityInput : uint8;
class UTDWAbilitySystemComponent;
struct FGameplayTag;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogTDWCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoveredActorDelegate, AActor*, HoveredActor);

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API ATDWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATDWPlayerController();

	bool GetHitUnderCursor(FHitResult& Hit) const;
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(BlueprintAssignable, Transient)
	FHoveredActorDelegate OnHoveredActor;
	
protected:
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void MoveInputPressed(const FInputActionValue& Value);

private:
	void AbilityInputPressed(FGameplayTag AbilityTag);
	void AbilityInputReleased(FGameplayTag AbilityTag);
	
	TWeakObjectPtr<UTDWAbilitySystemComponent> PawnASC;
	
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	
public:
	void SetPawnASC(UTDWAbilitySystemComponent* ASC);
};
