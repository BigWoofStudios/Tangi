// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "TangiGameplayTags.h"

namespace FTangiGameplayTags
{
	// -----------------------------------------------------------------------------------------------------------------
	// Input Tags
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, FName{TEXT("InputTag.Attack")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Aim, FName{TEXT("InputTag.Aim")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, FName{TEXT("InputTag.Sprint")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, FName{TEXT("InputTag.Jump")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch, FName{TEXT("InputTag.Crouch")});
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, FName{TEXT("InputTag.Move")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Cues
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Ability_HitReact, FName{TEXT("GameplayCue.Ability.HitReact")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Ability_Death, FName{TEXT("GameplayCue.Ability.Death")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Events
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event, FName{TEXT("Gameplay.Event")});
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event_Montage, FName{TEXT("Gameplay.Event.Montage")});
	UE_DEFINE_GAMEPLAY_TAG(Gameplay_Event_Montage_ActivateAbility, FName{TEXT("Gameplay.Event.Montage.ActivateAbility")});

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Abilities
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility, FName{TEXT("GameplayAbility")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_InputBlocked, FName{TEXT("GameplayAbility.InputBlocked")});

	//~ Common
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Death, FName{TEXT("GameplayAbility.Death")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_HitReact, FName{TEXT("GameplayAbility.HitReact")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_MeleeAttack, FName{TEXT("GameplayAbility.MeleeAttack")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_HoldBreath, FName{TEXT("GameplayAbility.HoldBreath")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Sprint, FName{TEXT("GameplayAbility.Sprint")});

	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Aim, FName{TEXT("GameplayAbility.Aim")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Block, FName{TEXT("GameplayAbility.Block")});
	
	// https://github.com/tranek/GASDocumentation?tab=readme-ov-file#4642-activation-failed-tags
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_BlockedByTags, FName{TEXT("GameplayAbility.Activation.Fail.BlockedByTags")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_CantAffordCost, FName{TEXT("GameplayAbility.Activation.Fail.CantAffordCost")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_IsDead, FName{TEXT("GameplayAbility.Activation.Fail.IsDead")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_MissingTags, FName{TEXT("GameplayAbility.Activation.Fail.MissingTags")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_Networking, FName{TEXT("GameplayAbility.Activation.Fail.Networking")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Activation_Fail_OnCooldown, FName{TEXT("GameplayAbility.Activation.Fail.OnCooldown")});
		
	//~ Costs
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cost, FName{TEXT("GameplayAbility.Cost")});
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cost_Sprint, FName{TEXT("GameplayAbility.Cost.Sprint")});

	//~ Cooldowns
	UE_DEFINE_GAMEPLAY_TAG(GameplayAbility_Cooldown, FName{TEXT("GameplayAbility.Cooldown")});

	// -----------------------------------------------------------------------------------------------------------------
	// Statuses
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Status, FName{TEXT("Status")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsDead, FName{TEXT("Status.IsDead")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsHitReacting, FName{TEXT("Status.IsHitReacting")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsUnderwater, FName{TEXT("Status.IsUnderwater")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsDrowning, FName{TEXT("Status.IsDrowning")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsSprinting, FName{TEXT("Status.IsSprinting")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsRegenerating_Health, FName{TEXT("Status.IsRegenerating.Health")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsRegenerating_Endurance, FName{TEXT("Status.IsRegenerating.Endurance")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsRegenerating_Oxygen, FName{TEXT("Status.IsRegenerating.Oxygen")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsFullHealth, FName{TEXT("Status.IsFullHealth")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsFullEndurance, FName{TEXT("Status.IsFullEndurance")});
	UE_DEFINE_GAMEPLAY_TAG(Status_IsFullOxygen, FName{TEXT("Status.IsFullOxygen")});
	
	// -----------------------------------------------------------------------------------------------------------------
	// Vital Attributes
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Health, FName{TEXT("Attribute.Vital.Health")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Endurance, FName{TEXT("Attribute.Vital.Endurance")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Vital_Oxygen, FName{TEXT("Attribute.Vital.Oxygen")});

	// -----------------------------------------------------------------------------------------------------------------
	// Primary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	// TODO: What should the primary attributes be?
	// // The positive or negative reputation one has.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Utu, FName{TEXT("Attribute.Primary.Utu")});
	// // This refers to the mana associated with land and territories; the power and authority derived from the ancestral connections to the land.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Whenua, FName{TEXT("Attribute.Primary.Whenua")});
	// // This pertains to the mana of people, reflecting their personal achievements, status, and influence.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Tangata, FName{TEXT("Attribute.Primary.Tangata")})
	// // This is the mana derived from the gods, representing the spiritual aspect and divine authority.
	// UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Atua, FName{TEXT("Attribute.Primary.Atua")})

	// -----------------------------------------------------------------------------------------------------------------
	// Secondary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxHealth, FName{TEXT("Attribute.Secondary.MaxHealth")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxEndurance, FName{TEXT("Attribute.Secondary.MaxEndurance")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxOxygen, FName{TEXT("Attribute.Secondary.MaxOxygen")});
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_CriticalHitChance, FName{TEXT("Attribute.Secondary.CriticalHitChance")});
	
	// -----------------------------------------------------------------------------------------------------------------
	// Movement Moves
	// -----------------------------------------------------------------------------------------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Walking, FName{TEXT("Movement.Mode.Walking")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_NavWalking, FName{TEXT("Movement.Mode.NavWalking")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Falling, FName{TEXT("Movement.Mode.Falling")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Swimming, FName{TEXT("Movement.Mode.Swimming")});
	UE_DEFINE_GAMEPLAY_TAG(Movement_Mode_Flying, FName{TEXT("Movement.Mode.Flying")});
	
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
