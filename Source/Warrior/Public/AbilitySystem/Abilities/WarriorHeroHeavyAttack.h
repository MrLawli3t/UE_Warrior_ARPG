// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorHeroMeleeAttack.h"
#include "WarriorHeroHeavyAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroHeavyAttack : public UWarriorHeroMeleeAttack
{
	GENERATED_BODY()

protected:
	virtual void PreMontageLogic() override;
};
