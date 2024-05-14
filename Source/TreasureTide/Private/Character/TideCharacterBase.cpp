// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TideCharacterBase.h"

// Sets default values
ATideCharacterBase::ATideCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATideCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATideCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATideCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

