// Copyright Big Woof Studios, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/TangiCharacterBase.h"
#include "Player/TangiPlayerController.h"
#include "Player/TangiPlayerState.h"
#include "TangiCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TANGI_API ATangiCharacter : public ATangiCharacterBase
{
	GENERATED_BODY()
public:
	ATangiCharacter();
	
	// Called on server
	virtual void PossessedBy(AController* NewController) override;

	// Called on Client
	virtual void OnRep_PlayerState() override;

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() override;

	ATangiPlayerController* GetTangiPlayerController();
	ATangiPlayerState* GetTangiPlayerState();
	UTangiAbilitySystemComponent* GetTangiAbilitySystemComponent();


private:
	UPROPERTY() ATangiPlayerState* TangiPlayerState = nullptr;
	UPROPERTY() ATangiPlayerController* TangiPlayerController = nullptr;
	UPROPERTY() UTangiAbilitySystemComponent* TangiAbilitySystemComponent = nullptr;
};
