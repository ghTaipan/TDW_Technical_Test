// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/TDWCharacterBase.h"
#include "TDWPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TDW_TECHNICAL_TEST_API ATDWPlayerCharacter : public ATDWCharacterBase
{
	GENERATED_BODY()

public:
	ATDWPlayerCharacter();
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
protected:
	virtual void InitializeAbilitySystem(const FTDWAbilitySystemInitializationSpec& InitData) override;
	virtual void PostInitializeAbilitySystem_Implementation() override;
	
public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
