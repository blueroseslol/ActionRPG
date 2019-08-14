#include "Abilities/Base/RPGAttributeSet.h"
#include "Abilities/Base/RPGAbilitySystemComponent.h"
#include "ActionRPG.h"
//#include "RPGCharacterBase.h"
//#include "GameplayEffect.h"
//#include "GameplayEffectExtension.h"

URPGAttributeSet::URPGAttributeSet() :
	Health(100), MaxHealth(100),Mana(10),MaxMana(10),
	AttackPower(1), DefensePower(0), Damage(0), MoveSpeed(300)
{
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	UE_LOG(LogActionRPG, Warning, TEXT("%s"), *FString(Attribute.AttributeName+FString::SanitizeFloat(NewValue)));
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);

}

void URPGAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}
