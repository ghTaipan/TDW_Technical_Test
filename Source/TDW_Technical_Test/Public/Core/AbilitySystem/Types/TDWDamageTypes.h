#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"

#include "TDWDamageTypes.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FTDWDamageSpec
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> DamageApplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> DamageReceiver;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftClassPtr<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FScalableFloat> DamageTypesToDamages;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag HitReactType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HitImpulseStrength = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DeathImpulseStrength = 1000.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageLevel = 1.0f;
};