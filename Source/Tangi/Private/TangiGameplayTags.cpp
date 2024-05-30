// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiGameplayTags.h"

namespace FTangiGameplayTags
{
	// -----------------------------------------------------------------------------------------------------------------
	// Input Tags
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, FName{TEXTVIEW("InputTag.Attack")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Aim, FName{TEXTVIEW("InputTag.Aim")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, FName{TEXTVIEW("InputTag.Sprint")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, FName{TEXTVIEW("InputTag.Jump")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch, FName{TEXTVIEW("InputTag.Crouch")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, FName{TEXTVIEW("InputTag.Move")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Cues
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Ability_HitReact, FName{TEXTVIEW("GameplayCue.Ability.HitReact")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Ability_Death, FName{TEXTVIEW("GameplayCue.Ability.Death")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Events
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event, FName{TEXTVIEW("Gameplay.Event")});
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event_Montage, FName{TEXTVIEW("Gameplay.Event.Montage")});
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event_Montage_ActivateAbility, FName{TEXTVIEW("Gameplay.Event.Montage.ActivateAbility")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Abilities
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility, FName{TEXTVIEW("GameplayAbility")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_InputBlocked, FName{TEXTVIEW("GameplayAbility.InputBlocked")});

	//~ Common
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Death, FName{TEXTVIEW("GameplayAbility.Death")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_HitReact, FName{TEXTVIEW("GameplayAbility.HitReact")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_MeleeAttack, FName{TEXTVIEW("GameplayAbility.MeleeAttack")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_HoldBreath, FName{TEXTVIEW("GameplayAbility.HoldBreath")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Sprint, FName{TEXTVIEW("GameplayAbility.Sprint")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_HealthRegeneration, FName{TEXTVIEW("GameplayAbility.Passive.HealthRegeneration")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_EnduranceRegeneration, FName{TEXTVIEW("GameplayAbility.Passive.EnduranceRegeneration")});

	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Aim, FName{TEXTVIEW("GameplayAbility.Aim")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Block, FName{TEXTVIEW("GameplayAbility.Block")});
	
	// https://github.com/tranek/GASDocumentation?tab=readme-ov-file#4642-activation-failed-tags
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_BlockedByTags, FName{"GameplayAbility.Activation.Fail.BlockedByTags"});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_CantAffordCost, FName{"GameplayAbility.Activation.Fail.CantAffordCost"});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_IsDead, FName{"GameplayAbility.Activation.Fail.IsDead"});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_MissingTags, FName{"GameplayAbility.Activation.Fail.MissingTags"});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_Networking, FName{"GameplayAbility.Activation.Fail.Networking"});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_OnCooldown, FName{"GameplayAbility.Activation.Fail.OnCooldown"});
		
	//~ Costs
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cost, FName{TEXTVIEW("GameplayAbility.Cost")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cost_Sprint, FName{TEXTVIEW("GameplayAbility.Cost.Sprint")});

	//~ Cooldowns
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cooldown, FName{TEXTVIEW("GameplayAbility.Cooldown")});

	// -----------------------------------------------------------------------------------------------------------------
	// Statuses
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Status, FName{TEXTVIEW("Status")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsDead, FName{TEXTVIEW("Status.IsDead")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsHitReacting, FName{TEXTVIEW("Status.IsHitReacting")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsUnderwater, FName{TEXTVIEW("Status.IsUnderwater")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsDrowning, FName{TEXTVIEW("Status.IsDrowning")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsSprinting, FName{TEXTVIEW("Status.IsSprinting")});

	// -----------------------------------------------------------------------------------------------------------------
	// Vital Attributes
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Health, FName{TEXTVIEW("Attribute.Vital.Health")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Endurance, FName{TEXTVIEW("Attribute.Vital.Endurance")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Oxygen, FName{TEXTVIEW("Attribute.Vital.Oxygen")});

	// -----------------------------------------------------------------------------------------------------------------
	// Primary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	// TODO: What should the primary attributes be?
	// // The positive or negative reputation one has.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Utu, FName{TEXTVIEW("Attribute.Primary.Utu")});
	// // This refers to the mana associated with land and territories; the power and authority derived from the ancestral connections to the land.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Whenua, FName{TEXTVIEW("Attribute.Primary.Whenua")});
	// // This pertains to the mana of people, reflecting their personal achievements, status, and influence.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Tangata, FName{TEXTVIEW("Attribute.Primary.Tangata")})
	// // This is the mana derived from the gods, representing the spiritual aspect and divine authority.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Atua, FName{TEXTVIEW("Attribute.Primary.Atua")})

	// -----------------------------------------------------------------------------------------------------------------
	// Secondary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxHealth, FName{TEXTVIEW("Attribute.Secondary.MaxHealth")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxEndurance, FName{TEXTVIEW("Attribute.Secondary.MaxEndurance")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxOxygen, FName{TEXTVIEW("Attribute.Secondary.MaxOxygen")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_CriticalHitChance, FName{TEXTVIEW("Attribute.Secondary.CriticalHitChance")});

	// -----------------------------------------------------------------------------------------------------------------
	// Movement Moves
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Walking, FName{TEXTVIEW("Movement.Mode.Walking")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_NavWalking, FName{TEXTVIEW("Movement.Mode.NavWalking")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Falling, FName{TEXTVIEW("Movement.Mode.Falling")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Swimming, FName{TEXTVIEW("Movement.Mode.Swimming")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Flying, FName{TEXTVIEW("Movement.Mode.Flying")});
	
	const TMap<uint8, FGameplayTag> MovementModeTagMap = {
			{MOVE_Walking, Movement_Mode_Walking},
			{MOVE_NavWalking, Movement_Mode_NavWalking},
			{MOVE_Falling, Movement_Mode_Falling},
			{MOVE_Swimming, Movement_Mode_Swimming},
			{MOVE_Flying, Movement_Mode_Flying},
	};

	FGameplayTag FindTagByString(const FString &TagString, const bool bMatchPartialString)
	{
		const UGameplayTagsManager &Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag &TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}
