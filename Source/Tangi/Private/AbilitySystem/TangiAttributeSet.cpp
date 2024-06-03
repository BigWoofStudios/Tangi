// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "AbilitySystem/TangiAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "TangiGameplayTags.h"
#include "AbilitySystem/TangiAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Player/TangiPlayerController.h"

UTangiAttributeSet::UTangiAttributeSet()
{
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Vital_Health, GetHealthAttribute);
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Vital_Endurance, GetEnduranceAttribute);
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Vital_Oxygen, GetOxygenAttribute);

	TagToAttribute.Add(FTangiGameplayTags::Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Secondary_MaxEndurance, GetMaxEnduranceAttribute);
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Secondary_MaxOxygen, GetMaxOxygenAttribute);
	TagToAttribute.Add(FTangiGameplayTags::Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
}

void UTangiAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, Oxygen, COND_None, REPNOTIFY_Always);

	// Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, MaxEndurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, MaxOxygen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTangiAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
}

void UTangiAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	if (Attribute == GetEnduranceAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxEndurance());
	if (Attribute == GetOxygenAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxOxygen());
}

void UTangiAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (GetIncomingDamageAttribute() == Data.EvaluatedData.Attribute)
	{
		DamagePostGameplayEffect(Props);
	}
	
	if (TSet{GetHealthAttribute(), GetMaxHealthAttribute()}.Contains(Data.EvaluatedData.Attribute))
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	
	if (TSet{GetEnduranceAttribute(), GetMaxEnduranceAttribute()}.Contains(Data.EvaluatedData.Attribute))
	{
		SetEndurance(FMath::Clamp(GetEndurance(), 0.f, GetMaxEndurance()));
	}
	
	if (TSet{GetOxygenAttribute(), GetMaxOxygenAttribute()}.Contains(Data.EvaluatedData.Attribute))
	{
		SetOxygen(FMath::Clamp(GetOxygen(), 0.f, GetMaxOxygen()));
	}
	
	HealthPostGameplayEffect();
	EndurancePostGameplayEffect();
	OxygenPostGameplayEffect();
}

void UTangiAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn *Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UTangiAttributeSet::ShowFloatingText(const FEffectProperties& Props, const float Damage, const bool bCriticalHit)
{
	// TODO: Get FloatingText working on damage 
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (ATangiPlayerController *SourcePlayerController = Cast<ATangiPlayerController>(Props.SourceCharacter->Controller))
		{
			SourcePlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, bCriticalHit);
		}
		else if (ATangiPlayerController *TargetPlayerController = Cast<ATangiPlayerController>(Props.TargetCharacter->Controller))
		{
			TargetPlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, bCriticalHit);
		}
	}
}

// -----------------------------------------------------------------------------------------------------------------
// Vital Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Vital Attributes
void UTangiAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, Health, OldValue);}
void UTangiAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, Endurance, OldValue);}
void UTangiAttributeSet::OnRep_Oxygen(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, Oxygen, OldValue);}

void UTangiAttributeSet::HealthPostGameplayEffect() const
{
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	const bool bIsDead = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Health_IsDead);
	const bool bIsFullHealth = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Health_IsFull);
	
	if (GetHealth() <= 0.f)
	{
		if (!bIsDead)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Health_IsDead);
		}
	}
	else if (bIsDead)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Health_IsDead);
	}
	
	if (GetHealth() >= GetMaxHealth())
	{
		if (!bIsFullHealth)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Health_IsFull);
		}
	}
	else if (bIsFullHealth)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Health_IsFull);
	}
}

void UTangiAttributeSet::EndurancePostGameplayEffect() const
{
	// Handle tags associated with this attribute
	const UAbilitySystemComponent *ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	const bool bIsExhausted = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Endurance_IsExhausted);
	const bool bIsFullEndurance = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Endurance_IsFull);
	
	if (GetEndurance()<= 0.f)
	{
		if (!bIsExhausted)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Endurance_IsExhausted);
		}
	}
	else if (bIsExhausted)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Endurance_IsExhausted);
	}

	if (GetEndurance() >= GetMaxEndurance())
	{
		if (!bIsFullEndurance)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Endurance_IsFull);
		}
	}
	else if (bIsFullEndurance)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Endurance_IsFull);
	}
}

void UTangiAttributeSet::AddReplicatedLooseTag(const FGameplayTag& Tag) const
{
	if ( UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
	{
		ASC->AddLooseGameplayTag(Tag);
		ASC->AddReplicatedLooseGameplayTag(Tag);
	}
}

void UTangiAttributeSet::RemoveReplicatedLooseTag(const FGameplayTag& Tag) const
{
	if ( UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(Tag);
		ASC->RemoveReplicatedLooseGameplayTag(Tag);
	}
}

void UTangiAttributeSet::OxygenPostGameplayEffect() const
{
	// Handle tags associated with this attribute
	const UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;

	// Check for underwater and oxygen levels
	const bool bIsUnderwater = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_IsUnderwater);
	const bool bIsDrowning = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
	const bool bIsDead = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Health_IsDead);
	const bool bIsOxygenFull = ASC->HasMatchingGameplayTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsFull);

	// Handle drowning tag logic
	if (GetOxygen() <= 0.f && bIsUnderwater)
	{
		if (bIsDead && bIsDrowning)
		{
			RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
		}
		else if (!bIsDrowning)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
		}
	}
	else if (bIsDrowning)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsDrowning);
	}

	// Handle oxygen full tag logic
	if (GetOxygen() >= GetMaxOxygen())
	{
		if (!bIsOxygenFull)
		{
			AddReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsFull);
		}
	}
	else if (bIsOxygenFull)
	{
		RemoveReplicatedLooseTag(FTangiGameplayTags::Status_Attribute_Oxygen_IsFull);
	}
}
#pragma endregion

// -----------------------------------------------------------------------------------------------------------------
// Secondary Attributes
// -----------------------------------------------------------------------------------------------------------------
#pragma region Secondary Attributes
void UTangiAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, MaxHealth, OldValue);}
void UTangiAttributeSet::OnRep_MaxEndurance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, MaxEndurance, OldValue);}
void UTangiAttributeSet::OnRep_MaxOxygen(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, MaxOxygen, OldValue);}
void UTangiAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const {GAMEPLAYATTRIBUTE_REPNOTIFY(UTangiAttributeSet, CriticalHitChance, OldValue);}

void UTangiAttributeSet::DamagePostGameplayEffect(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);
		
	const bool bCriticalHit = UTangiAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		
	if (LocalIncomingDamage > 0.f)
	{
		// TODO: Can check for things like blocked or parried hit
		FGameplayTagContainer TagContainer;
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		if (NewHealth <= 0.f)
		{
			TagContainer.AddTagFast(FTangiGameplayTags::GameplayAbility_Death);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
		else
		{
			TagContainer.AddTagFast(FTangiGameplayTags::GameplayAbility_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		}
	}
		
	ShowFloatingText(Props, LocalIncomingDamage, bCriticalHit);
}
#pragma endregion
