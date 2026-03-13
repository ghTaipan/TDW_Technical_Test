#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

/**
 * Where we store all the relevant gameplay tags
 */

namespace NativeGameplayTags
{
	namespace Ability
	{
		namespace Combat
		{
			namespace Offensive
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Combat_Offensive_Leap_Slam)
			}
		}
		
		namespace CharacterState
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Character_State_Hit_React)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Character_State_Death)
		}
	}

	namespace Event
	{
		namespace Combat
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Event_Combat_Hit_Detected)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Event_Combat_Hit_React)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Event_Combat_Enable_Ragdoll)
		}
	}
	namespace Attribute
	{
		namespace Max
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Max_Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Max_Mana)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Max_Attack_Speed)
		}
		
		namespace Current
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Current_Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Current_Mana)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Current_Attack_Speed)
		}

		namespace Regeneration
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attribute_Regeneration_Mana)
		}
		
		
		namespace State
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Mana)
		}
	}
	
	namespace DamageType
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Type)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Damage_Physical_Type)
		
		const TArray<FGameplayTag>& GetDamageTypeTags();
	}
	
	namespace HitReactType
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_HitReactType_Light)
	}
	namespace Character
	{
		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_Player)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_Test_Dummy)
		}
	}
}