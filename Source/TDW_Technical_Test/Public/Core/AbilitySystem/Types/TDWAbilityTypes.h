#pragma once

#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "ScalableFloat.h"
#include "TDWDamageTypes.h"
#include "TDWAbilityTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

USTRUCT(Blueprintable)
struct FTDWAttributeMaxValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FScalableFloat MaxFloat{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute MaxAttribute{};
};

USTRUCT(Blueprintable)
struct FTDWAttributeInitializer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FScalableFloat Value;
};

// Contains data used to initialize an Ability System Component.
USTRUCT(BlueprintType)
struct FTDWAbilitySystemInitializationSpec
{

	GENERATED_BODY()
	
	// An array of Attribute Sets to create.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UAttributeSet>> AttributeSets;

	// A map of Attributes / float used to set base values.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FGameplayAttribute, FTDWAttributeInitializer> AttributeBaseValues;

	// An Array of Gameplay Abilities to give.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	// An array of Gameplay Effects to apply.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	// A container of GameplayTags to apply.
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTagContainer GameplayTags;
};

USTRUCT(BlueprintType)
struct FTDWGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
	// not implemented NetSerialize nor TStructOpsTypeTraits since the project is going to be a single-player experience
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FTDWGameplayEffectContext::StaticStruct();
	}
	
	virtual FTDWGameplayEffectContext* Duplicate() const override
	{
		FTDWGameplayEffectContext* NewContext = new FTDWGameplayEffectContext();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		
		NewContext->DamageSpec = DamageSpec;
		
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		
		return NewContext;
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTDWDamageSpec DamageSpec = FTDWDamageSpec();
	
public:
	FTDWDamageSpec GetDamageSpec() const {return DamageSpec;}
	void SetDamageSpec(const FTDWDamageSpec& InDamageSpec) {DamageSpec = InDamageSpec;}
};