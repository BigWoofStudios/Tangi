// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/TangiGameplayEffectContext.h"

bool FTangiGameplayEffectContext::NetSerialize(FArchive &Ar, UPackageMap *Map, bool &bOutSuccess)
{
	uint32 RepBits = 0;
	if (Ar.IsSaving())
	{
		if (bReplicateInstigator && Instigator.IsValid())
		{
			RepBits |= 1 << 0;
		}
		if (bReplicateEffectCauser && EffectCauser.IsValid())
		{
			RepBits |= 1 << 1;
		}
		if (AbilityCDO.IsValid())
		{
			RepBits |= 1 << 2;
		}
		if (bReplicateSourceObject && SourceObject.IsValid())
		{
			RepBits |= 1 << 3;
		} 
		if (Actors.Num() > 0)	
		{
			RepBits |= 1 << 4;
		}
		if (HitResult.IsValid())
		{
			RepBits |= 1 << 5;
		}
		if (bHasWorldOrigin)	
		{
			RepBits |= 1 << 6;
		}
		
		//~ Custom bits
		if (bIsCriticalHit)	RepBits |= 1 << 7;
	}

	Ar.SerializeBits(&RepBits, 7 /* Original amount */ + 1 /* # of custom bits*/);

	if (RepBits & (1 << 0))
	{
		Ar << Instigator;
	}
	if (RepBits & (1 << 1))
	{
		Ar << EffectCauser;
	}
	if (RepBits & (1 << 2))
	{
		Ar << AbilityCDO;
	}
	if (RepBits & (1 << 3))
	{
		Ar << SourceObject;
	}
	if (RepBits & (1 << 4))
	{
		SafeNetSerializeTArray_Default<31>(Ar, Actors);
	}
	if (RepBits & (1 << 5))
	{
		if (Ar.IsLoading())
		{
			if (!HitResult.IsValid())
			{
				HitResult = MakeShared<FHitResult>();
			}
		}
		HitResult->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 6))
	{
		Ar << WorldOrigin;
		bHasWorldOrigin = true;
	}
	else
	{
		bHasWorldOrigin = false;
	}

	//~ Custom bits
	if (RepBits & (1 << 7))  Ar << bIsCriticalHit;

	if (Ar.IsLoading())
	{
		// Just to initialize InstigatorAbilitySystemComponent
		AddInstigator(Instigator.Get(), EffectCauser.Get());
	}	
	
	bOutSuccess = true;
	return true;
}