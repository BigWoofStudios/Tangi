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
		InPlace, TEXTVIEW("TrackMeleeCollision: ")
	};

	return FString{NotifyNameBuilder};
}

void UAnimNotifyState_TrackMeleeCollision::NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation, const float Duration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(Mesh, Animation, Duration, EventReference);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Mesh->GetOwner());
	if (!CombatInterface) return;

	ActiveWeaponMesh = CombatInterface->GetActiveWeaponMesh();

	if (ActiveWeaponMesh)
	{
		ActiveWeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &UAnimNotifyState_TrackMeleeCollision::OnComponentOverlap);
	}
}

void UAnimNotifyState_TrackMeleeCollision::NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(Mesh, Animation, EventReference);

	if (ActiveWeaponMesh)
	{
		ActiveWeaponMesh->OnComponentBeginOverlap.RemoveDynamic(this, &UAnimNotifyState_TrackMeleeCollision::OnComponentOverlap);
		ActiveWeaponMesh = nullptr;
	}
}

void UAnimNotifyState_TrackMeleeCollision::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
