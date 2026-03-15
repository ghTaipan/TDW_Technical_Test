// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "TDWCharacterBase.generated.h"

class UTDWCharacterAssets;
struct FTDWAbilitySystemInitializationSpec;
class UTDWAbilitySystemComponent;

UCLASS(Abstract, NotBlueprintable)
class TDW_TECHNICAL_TEST_API ATDWCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDWCharacterBase();

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void InitializeAbilitySystem(const FTDWAbilitySystemInitializationSpec& InitData);
	// Will be fired after ASC initialized.
	UFUNCTION(BlueprintNativeEvent)
	void PostInitializeAbilitySystem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTDWAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FGameplayTagContainer CharacterSpecTags;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTDWCharacterAssets> CharacterAssets;
	
public:	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	const FGameplayTagContainer& GetCharacterSpecTags() const {return CharacterSpecTags;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTDWCharacterAssets* GetCharacterAssets() const {return CharacterAssets;}
};
