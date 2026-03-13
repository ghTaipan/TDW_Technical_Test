#pragma once

#include "TDWActionDirectionTypes.generated.h"

UENUM(BlueprintType)
enum class EActionDirection: uint8
{
	NoDirection		UMETA(DisplayName = "NoDirection"),
	Clock12			UMETA(DisplayName = "Clock12"),
	Clock1_5		UMETA(DisplayName = "Clock1:30"),
	Clock3			UMETA(DisplayName = "Clock3"),
	Clock4_5		UMETA(DisplayName = "Clock4:30"),
	Clock6			UMETA(DisplayName = "Clock6"),
	Clock7_5		UMETA(DisplayName = "Clock7:5"),
	Clock9			UMETA(DisplayName = "Clock9"),
	Clock10_5		UMETA(DisplayName = "Clock10:30"),
	Count			UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EActionDirection, EActionDirection::Count)