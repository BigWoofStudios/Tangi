// Copyright Big Woof Studios, LLC. All Rights Reserved.


#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Combat/CombatInterface.h"
#include "AnimNotifyState_TrackMeleeCollision.generated.h"

UCLASS(DisplayName = "Track Melee Collision Animation Notify State")
class TANGI_API UAnimNotifyState_TrackMeleeCollision : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_TrackMeleeCollision();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation, float Duration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> ActiveWeaponMesh;

	ICombatInterface* ThisCombatInterface = nullptr;
};
