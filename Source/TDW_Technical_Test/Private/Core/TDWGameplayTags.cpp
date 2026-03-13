#include "Core/TDWGameplayTags.h"

namespace NativeGameplayTags
{
	namespace Ability
	{
		namespace Combat
		{
			namespace Offensive
			{
				UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Ability_Combat_Offensive_Leap_Slam, "Ability.Combat.Offensive.LeapSlam", "")
			}
		}
		
		namespace CharacterState
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Ability_Character_State_Hit_React, "Ability.CharacterState.HitReact", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Ability_Character_State_Death, "Ability.CharacterState.Death", "")
		}
	}
	
	namespace Event
	{
		namespace Combat
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Combat_Hit_Detected, "Event.Combat.HitDetected", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Combat_Hit_React, "Event.Combat.HitReact", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Combat_Enable_Ragdoll, "Event.Combat.EnableRagdoll", "")
		}
	}
	
	namespace Attribute
	{
		namespace Max
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Max_Health, "Attributes.Max.Health", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Max_Mana, "Attributes.Max.Mana", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Max_Attack_Speed, "Attributes.Max.AttackSpeed", "")
		}
		namespace Current
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Current_Health, "Attributes.Current.Health", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Current_Mana, "Attributes.Current.Mana", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Current_Attack_Speed, "Attributes.Current.AttackSpeed", "")
		}
		namespace Regeneration
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Regeneration_Mana, "Attributes.Regeneration.Mana", "")
		}

		
		namespace State
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Mana, "Attributes.State.MaxMana", "")
		}
	}
	
	namespace DamageType
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Type, "DamageType", "")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Type_Physical, "DamageType.Physical", "")
		
		const TArray<FGameplayTag>& GetDamageTypeTags(){
			static TArray<FGameplayTag> AbilityTags;
			if (AbilityTags.Num() == 0)
			{
				AbilityTags.Append(UGameplayTagsManager::Get().RequestGameplayTagChildren(TAG_Damage_Type).GetGameplayTagArray());
			}
			
			return AbilityTags;
		}
	}
	
	namespace HitReactType
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_HitReactType_Light, "HitReactType.Light", "")
	}
	
	namespace Character
	{
		namespace Type
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_Player, "Character.Type.Player", "")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_Test_Dummy, "Character.Type.TestDummy", "")
		}
	}
}