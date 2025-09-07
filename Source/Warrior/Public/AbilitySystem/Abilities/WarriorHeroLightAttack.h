// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorHeroMeleeAttack.h"
#include "WarriorHeroLightAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroLightAttack : public UWarriorHeroMeleeAttack
{
	GENERATED_BODY()

protected:
	virtual void PostMontageLogic() override;
	virtual void OnResetComboTimer() override;

};
