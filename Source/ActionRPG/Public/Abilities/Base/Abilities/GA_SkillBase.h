#pragma once

#include "CoreMinimal.h"
#include "Abilities/Base/RPGGameplayAbility.h"
#include "GA_SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UGA_SkillBase : public URPGGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_SkillBase();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
