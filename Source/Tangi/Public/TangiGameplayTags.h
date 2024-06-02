// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

namespace FTangiGameplayTags
{
	// -----------------------------------------------------------------------------------------------------------------
	// Input Tags
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Aim);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sprint);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Cues
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Ability_HitReact);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Ability_Death);

	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Events
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_Event);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_Event_Montage);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Gameplay_Event_Montage_ActivateAbility);
	
	// -----------------------------------------------------------------------------------------------------------------
	// Gameplay Abilities
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_InputBlocked);
	
	//~ Common
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Death);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Drown);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_HoldBreath);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_HitReact);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_MeleeAttack);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Sprint);

	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Aim);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Block);
	
	// https://github.com/tranek/GASDocumentation?tab=readme-ov-file#4642-activation-failed-tags
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_BlockedByTags);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_CantAffordCost);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_IsDead);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_MissingTags);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_Networking);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Activation_Fail_OnCooldown);
	
	//~ Costs
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cost);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cost_Sprint);

	//~ Cooldowns
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cooldown);

	// -----------------------------------------------------------------------------------------------------------------
	// Statuses
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status);
	
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_IsHitReacting);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_IsUnderwater);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_IsSprinting);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Health_IsRegenerating);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Health_IsFull);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Health_IsDead);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Endurance_IsRegenerating);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Endurance_IsFull);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Endurance_IsExhausted);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Oxygen_IsRegenerating);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Oxygen_IsFull);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Attribute_Oxygen_IsDrowning);

	// -----------------------------------------------------------------------------------------------------------------
	// Vital Attributes
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Endurance);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Oxygen);

	// -----------------------------------------------------------------------------------------------------------------
	// Primary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	// TODO: What should the primary attributes be?
	// TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Utu);
	// TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Whenua);
	// TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Tangata);
	// TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Atua);

	// -----------------------------------------------------------------------------------------------------------------
	// Secondary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxHealth);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxEndurance);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxOxygen);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitChance);

	// -----------------------------------------------------------------------------------------------------------------
	// Movement Moves
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	TANGI_API extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
};
