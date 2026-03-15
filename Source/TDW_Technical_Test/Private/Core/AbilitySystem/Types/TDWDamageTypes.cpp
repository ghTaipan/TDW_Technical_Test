
#include "Core/AbilitySystem/Types/TDWDamageTypes.h"

#include "GameplayEffect.h"

bool FTDWDamageSpec::IsValid() const
{
	return ::IsValid(DamageEffectClass);
}
