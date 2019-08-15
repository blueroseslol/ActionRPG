#include "DamageMagnitudeCalculation.h"
#include "Abilities/Base/RPGAttributeSet.h"
#include "GameplayEffect.h"

UDamageMagnitudeCalculation::UDamageMagnitudeCalculation()
{
	RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(FGameplayAttribute(FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)))
		, EGameplayEffectAttributeCaptureSource::Source, false));
}

float UDamageMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float damage{ 0.0f};

	FAggregatorEvaluateParameters InEvalParams;

	//捕获失败的容错语句
	if (!GetCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(FGameplayAttribute(FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)))
		, EGameplayEffectAttributeCaptureSource::Source, false), Spec, InEvalParams, damage)) {
		damage = 1.0f;
	}

	return damage;
}