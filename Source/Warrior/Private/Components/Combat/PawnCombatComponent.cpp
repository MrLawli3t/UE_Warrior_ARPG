// Lawliet Studios All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"

#include "WarriorDebugHelper.h"
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

	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag: %s"), *InWeaponToRegister->GetName(),
		*InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
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
