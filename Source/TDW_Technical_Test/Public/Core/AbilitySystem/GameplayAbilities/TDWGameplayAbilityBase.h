// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TDWGameplayAbilityBase.generated.h"

class UTDWAbilitySystemComponent;
class ATDWCharacterBase;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UTDWGameplayAbilityBase();
	
protected:
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	TWeakObjectPtr<ATDWCharacterBase> BaseCharacter;
	TWeakObjectPtr<UTDWAbilitySystemComponent> ASC;
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UAnimMontage> MontageToPlay;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ATDWCharacterBase* GetBaseCharacter() const {return BaseCharacter.Get();}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTDWAbilitySystemComponent* GetASC() const {return ASC.Get();}
};
