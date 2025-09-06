// Lawliet Studios All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "WarriorGameplayTags.h"
#include "Items/Weapons/WarriorWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A tag named %s has already been registered"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	InWeaponToRegister->HitActorDelegate.BindUObject(this, &UPawnCombatComponent::OnHitActor);

	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag: %s"), *InWeaponToRegister->GetName(),
		*InWeaponTagToRegister.ToString());
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{ 
	if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTag))
	{
		return *FoundWeapon;
	}
	
	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::OnHitActor(AActor* HitActor)
{
	FGameplayEventData HitEventPayload;
	HitEventPayload.Target = HitActor;
	HitEventPayload.Instigator = GetOwningPawn();
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		HitActor,
		WarriorGameplayTags::Shared_Event_MeleeHit,
		HitEventPayload
	);
}
