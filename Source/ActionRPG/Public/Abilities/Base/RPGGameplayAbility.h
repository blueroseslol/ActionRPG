#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "Abilities/Base/RPGAbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	URPGGameplayAbility();

	/** Gameplay标签与GameplayEffect Map */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FRPGGameplayEffectContainer> EffectContainerMap;

	/** 读取指定的FRPGGameplayEffectContainer来生成FRPGGameplayEffectContainerSpec */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FRPGGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FRPGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** 通过GameplayTag来搜索EffectContainerMap，并且生成FRPGGameplayEffectContainerSpec */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FRPGGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** 让FRPGGameplayEffectContainerSpec中的effect对指定目标生效 */
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec);

	/** 调用MakeEffectContainerSpec生成FRPGGameplayEffectContainerSpec，再让Effect对目标生效 */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
};
