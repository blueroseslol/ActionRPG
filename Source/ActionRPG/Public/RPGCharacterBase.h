#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Base/RPGAttributeSet.h"
#include "Abilities/Base/RPGAbilitySystemComponent.h"
#include "RPGCharacterBase.generated.h"

UCLASS(config = Game)
class ACTIONRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
protected:
	//用于存储角色类的GameplayAbility并且在角色启用时注册
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<URPGGameplayAbility>> GameplayAbilities;

	//GameplayAbility组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameplayAbilities, meta = (AllowPrivateAccess = "true"))
	class URPGAbilitySystemComponent* AbilitySystemComponent;

	//属性集
	UPROPERTY()
	URPGAttributeSet* AttributeSet;

	//判断GameplayAbility是否已经初始化
	UPROPERTY()
	bool bAbilitiesInitialized;
public:
	ARPGCharacterBase();
protected:
	//向GameplayAbilityComponent注册GameplayAbility
	void AddStartupGameplayAbilities();

	//从GameplayAbilityComponent注销之前注册的GameplayAbility
	void RemoveStartupGameplayAbilities();
private:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
public:
	//用于在角色启用前注册GameplayAbility
	virtual void PossessedBy(AController* NewController) override;
};
