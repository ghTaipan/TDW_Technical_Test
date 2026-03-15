#pragma once

#include "CoreMinimal.h"
#include "TDWWidgetControllerBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FTDWWidgetControllerParams
{
	GENERATED_BODY()

	FTDWWidgetControllerParams() {}
	
	FTDWWidgetControllerParams(UAbilitySystemComponent* ASC, const TArray<const UAttributeSet*>& AS) :
	AbilitySystemComponent(ASC), AttributeSets(AS) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<const UAttributeSet>> AttributeSets;
};

/**
 * This class is the bridge between the UI and the Ability System.
 */
UCLASS(Abstract)
class TDW_TECHNICAL_TEST_API UTDWWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FTDWWidgetControllerParams& WCParams);

	virtual void BroadCastInitialValues();
	virtual void BindCallbacksToDependencies();

protected:
	
	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category= "WidgetController")
	TArray<TObjectPtr<const UAttributeSet>> AttributeSet;
	
	UAbilitySystemComponent* GetASC() const {return  AbilitySystemComponent;}
	const TArray<const UAttributeSet*>& GetAttributeSets() const {return  AttributeSet;}
};
