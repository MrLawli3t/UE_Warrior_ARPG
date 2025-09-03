// Lawliet Studios All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "WarriorDebugHelper.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(FName("CombatComponent"));
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent()
{
	return CombatComponent;
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartupData();
}

void AWarriorEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartupData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		 CharacterStartupData.ToSoftObjectPath(),
		 FStreamableDelegate::CreateLambda([this]()
		 {
		 	if (UDataAsset_StartupDataBase* LoadedData = CharacterStartupData.Get())
		 	{
		 		LoadedData->GiveAbilitiesToAbilitySystemComponent(WarriorAbilitySystemComponent);
		 		Debug::Print(TEXT("Enemy Startup Data Loaded"), FColor::Green);
		 	}
		 })
	);
}
