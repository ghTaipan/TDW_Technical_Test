// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/Types/TDWActionDirectionTypes.h"
#include "Core/Types/TDWTypes.h"
#include "Engine/DataAsset.h"
#include "TDWCharacterAssets.generated.h"

USTRUCT(BlueprintType)
struct FDirectionMontageSpec
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EActionDirection, UAnimMontage*> HitReactMontages;
};

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UTDWCharacterAssets : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, UAnimMontage*> SkillMontages;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FDirectionMontageSpec> HitReactMontages;
	// Couldn't find right and left death montages.
	UPROPERTY(EditDefaultsOnly)
    FDirectionMontageSpec DeathMontages;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FSoundBaseArray> HitReactSounds;
	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> DeathSounds;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FGameplayTag, UAnimMontage*>& GetSkillMontages() const {return SkillMontages;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FGameplayTag, FDirectionMontageSpec>& GetHitReactMontages() const {return HitReactMontages;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FDirectionMontageSpec& GetDeathMontages() const {return DeathMontages;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FGameplayTag, FSoundBaseArray>& GetHitReactSounds() const {return HitReactSounds;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<USoundBase*>& GetDeathSounds() const {return DeathSounds;}
};
