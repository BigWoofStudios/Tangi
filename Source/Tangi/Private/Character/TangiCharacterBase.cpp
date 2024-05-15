// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "Character/TangiCharacterBase.h"

// Sets default values
ATangiCharacterBase::ATangiCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATangiCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATangiCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATangiCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

