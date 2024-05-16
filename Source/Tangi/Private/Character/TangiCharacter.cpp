// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "UI/HUD/TangiHUD.h"

ATangiCharacter::ATangiCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	if (IsValid(GetMesh()))
	{
		// Drop character mesh down flush with floor/ in position with capsule component
		// and rotate to face the forward direction, as indicated by the arrow in ACharacter
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.f, 0.f, -92.f),
			FRotator(0.f, -90.f, 0.f));
	}
}

void ATangiCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//~ Server-specific initialization
	InitAbilityActorInfo();
	AddCharacterAbilities();
	InitializeDefaultAttributes();
}

void ATangiCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//~ Client-specific initialization
	InitAbilityActorInfo();
	if (GetTangiPlayerController())
	{
		if (ATangiHUD* TangiHUD = Cast<ATangiHUD>(GetTangiPlayerController()->GetHUD()))
		{
			TangiHUD->InitOverlay(GetTangiPlayerController(), GetTangiPlayerState(), AbilitySystemComponent, AttributeSet);
		}
	}
}

void ATangiCharacter::InitAbilityActorInfo()
{
	check(GetTangiPlayerState());
	GetTangiPlayerState()->GetAbilitySystemComponent()->InitAbilityActorInfo(GetTangiPlayerState(), this);
	GetTangiAbilitySystemComponent()->SetTagRelationshipMapping(TagRelationshipMapping);
	GetTangiAbilitySystemComponent()->AbilityActorInfoSet();
	
	// Assign references to ASC & AS on player character
	AbilitySystemComponent = GetTangiPlayerState()->GetAbilitySystemComponent();
	AttributeSet = GetTangiPlayerState()->GetAttributeSet();
}

void ATangiCharacter::InitializeDefaultAttributes()
{
	// Initialize default attributes for character
	Super::InitializeDefaultAttributes();
}

ATangiPlayerController* ATangiCharacter::GetTangiPlayerController()
{
	if (TangiPlayerController == nullptr)
	{
		TangiPlayerController = Cast<ATangiPlayerController>(GetController());
	}

	return TangiPlayerController;
}

ATangiPlayerState* ATangiCharacter::GetTangiPlayerState()
{
	if (TangiPlayerState == nullptr)
	{
		TangiPlayerState = GetPlayerState<ATangiPlayerState>();
	}

	return TangiPlayerState;
}

UTangiAbilitySystemComponent* ATangiCharacter::GetTangiAbilitySystemComponent()
{
	if (TangiAbilitySystemComponent == nullptr)
	{
		TangiAbilitySystemComponent = Cast<UTangiAbilitySystemComponent>(GetTangiPlayerState()->GetAbilitySystemComponent());
	}

	return TangiAbilitySystemComponent;
}
