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
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_HitReact);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_MeleeAttack);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Sprint);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_HealthRegeneration);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_EnduranceRegeneration);

	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Aim);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Block);
	
	//~ Failed to activate tags
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GamplayAbility_ActivateFail_IsDead);

	//~ Costs
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cost);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cost_Sprint);

	//~ Cooldowns
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayAbility_Cooldown);

	// -----------------------------------------------------------------------------------------------------------------
	// Statuses
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_IsDead);

	// -----------------------------------------------------------------------------------------------------------------
	// Vital Attributes
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Endurance);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Oxygen);

	// -----------------------------------------------------------------------------------------------------------------
	// Primary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Whenua);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Tangata);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Atua);

	// -----------------------------------------------------------------------------------------------------------------
	// Secondary Attributes
	// -----------------------------------------------------------------------------------------------------------------
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxHealth);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxEndurance);
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxOxygen);

	// Positive Utu:
	// - When a family hosts a feast or provides help, the recipients are expected to reciprocate in the future, creating a cycle of generosity and mutual support.
	// - Acts of kindness and hospitality are repaid, strengthening community ties and fostering goodwill.
	//
	// Negative Utu:
	// - In cases of offense or injury, utu can involve seeking reparation or retaliation to address the wrong. This might include demanding compensation, returning stolen goods, or, in severe cases, seeking vengeance.
	// - Traditionally, negative utu could lead to cycles of retribution, but contemporary understandings emphasize reconciliation and restorative justice.
	TANGI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Utu);

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
