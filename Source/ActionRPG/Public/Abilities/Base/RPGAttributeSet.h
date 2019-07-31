// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

//ʹ��AttributeSet.h�ĺ�
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class ACTIONRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	URPGAttributeSet();
	//��д�ӿ�
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//����ֵ
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

	//�������ֵ
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)

	//����ֵ
	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Mana)

	//�������ֵ
	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana)

	//������
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackPower)

	//������
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, DefensePower)

	//ħ���˺�
	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)

	//�ƶ��ٶ�
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MoveSpeed)
public:
	//�����ֵ�ı�ʱ������ǰֵ���޸�Ϊ��ȷ��ֵ
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
