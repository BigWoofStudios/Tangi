// Copyright Big Woof Studios, LLC. All Rights Reserved.

#include "Character/Animation/AnimNotifyState_TrackMeleeCollision.h"

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
	if (ThisCombatInterface != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "NotifyTick");
	}
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_TrackMeleeCollision::NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
                                                       const float Duration, const FAnimNotifyEventReference& EventReference)
{
	ThisCombatInterface = Cast<ICombatInterface>(Mesh->GetOwner());
	Super::NotifyBegin(Mesh, Animation, Duration, EventReference);
}

void UAnimNotifyState_TrackMeleeCollision::NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ThisCombatInterface = nullptr;
	Super::NotifyEnd(Mesh, Animation, EventReference);
}
