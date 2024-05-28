// Copyright Big Woof Studios, LLC. All Rights Reserved.

#include "Character/Animation/AnimNotifyState_TrackMeleeCollision.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TangiGameplayTags.h"
#include "Combat/CombatInterface.h"
#include "Components/SkeletalMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AnimNotifyState_TrackMeleeCollision)

UAnimNotifyState_TrackMeleeCollision::UAnimNotifyState_TrackMeleeCollision()
{
	bIsNativeBranchingPoint = true;
}

FString UAnimNotifyState_TrackMeleeCollision::GetNotifyName_Implementation() const
{
	TStringBuilder<256> NotifyNameBuilder{
		InPlace, TEXTVIEW("TrackMeleeCollision")
	};

	return FString{NotifyNameBuilder};
}

void UAnimNotifyState_TrackMeleeCollision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                      const float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Owner))
	{
		TArray<AActor*> OverlappingActors;
		CombatInterface->GetActiveWeaponMesh()->GetOverlappingActors(OverlappingActors);
		for (AActor* OverlapActor : OverlappingActors)
		{
			if (OverlapActor == Owner) continue;
			if (!OverlapActor->Implements<UCombatInterface>()) continue;

			// Send a gameplay event to the owner of this anim notify state, so they can respond to the hit
			FGameplayEventData GameplayEventData;
			GameplayEventData.Target = OverlapActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, FTangiGameplayTags::Gameplay_Event_Montage_ActivateAbility, GameplayEventData);
		}
	}

	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}
