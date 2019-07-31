#include "RPGCharacterBase.h"
#include "GameFramework/Controller.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Base/RPGAbilitySystemComponent.h"
#include "Abilities/Base/RPGGameplayAbility.h"
#include "ActionRPG.h"

ARPGCharacterBase::ARPGCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));

	bAbilitiesInitialized = false;
}


void ARPGCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AddStartupGameplayAbilities();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGCharacterBase::AddStartupGameplayAbilities()
{
	if (!bAbilitiesInitialized)
	{
		for (TSubclassOf<URPGGameplayAbility>& StartupAbility : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
		}
		bAbilitiesInitialized = true;

		UE_LOG(LogActionRPG, Warning, TEXT("%s"), *FString("All Ablities registered"));
	}
}

void ARPGCharacterBase::RemoveStartupGameplayAbilities()
{
	if (bAbilitiesInitialized)
	{
		TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
		for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			if ((Spec.SourceObject == this) && GameplayAbilities.Contains(Spec.Ability->GetClass()))
			{
				AbilitiesToRemove.Add(Spec.Handle);
			}
		}

		for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		{
			AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
		}
		bAbilitiesInitialized = false;
	}
}


