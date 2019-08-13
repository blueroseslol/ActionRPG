#include "Abilities/Base/Abilities/GA_SkillBase.h"
#include "Abilities/Base/Effects/GE_DamageBase.h"
#include "ActionRPG.h"
UGA_SkillBase::UGA_SkillBase()
{

}

void UGA_SkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (bHasBlueprintActivate)
	{
		// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
		K2_ActivateAbility();
	}
	else if (bHasBlueprintActivateFromEvent)
	{
		if (TriggerEventData)
		{
			// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
			K2_ActivateAbilityFromEvent(*TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
	}
	else
	{
		// Native child classes may want to override ActivateAbility and do something like this:

		// Do stuff...

		if (CommitAbility(Handle, ActorInfo, ActivationInfo))		// ..then commit the ability...
		{			
			//	Then do more stuff...
			UE_LOG(LogActionRPG, Warning, TEXT("%s"), *FString("A Ablities Activate"));

			const UGameplayEffect* GameplayEffect = NewObject<UGE_DamageBase>();
			ApplyGameplayEffectToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, GameplayEffect, 1, 1);

			K2_EndAbility();
		}
	}
}
