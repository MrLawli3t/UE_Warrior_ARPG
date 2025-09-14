// Lawliet Studios All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/WarriorHeroWeapon.h"


UHeroCombatComponent::UHeroCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(const FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetEquippedWeaponScaledDamage(const float Level) const
{
	if (const AWarriorHeroWeapon* Weapon = GetHeroCurrentEquippedWeapon())
	{
		return Weapon->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(Level);
	}

	return 0.0f;
}

