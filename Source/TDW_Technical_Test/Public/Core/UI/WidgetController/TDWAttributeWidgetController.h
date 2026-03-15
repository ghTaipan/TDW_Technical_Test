#pragma once

#include "Core/AbilitySystem/Types/TDWAttributeTypes.h"
#include "TDWWidgetControllerBase.h"

#include "TDWAttributeWidgetController.generated.h"

class UTDWAttributeData;
struct FGameplayAttribute;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FTDWAttributeSpec&, Spec);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TDW_TECHNICAL_TEST_API UTDWAttributeWidgetController : public UTDWWidgetControllerBase
{
	GENERATED_BODY()
	
public:
	virtual void BroadCastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Transient, Category="Gas|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

private:
	void BroadCastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTDWAttributeData> AttributeData;
};
