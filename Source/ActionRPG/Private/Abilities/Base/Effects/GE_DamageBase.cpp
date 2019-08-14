#include "Abilities/Base/Effects/GE_DamageBase.h"
#include "Abilities/Base/RPGAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
UGE_DamageBase::UGE_DamageBase()
{
	//持续
	/*
	DurationPolicy = EGameplayEffectDurationType::HasDuration;

	DurationMagnitude = FGameplayEffectModifierMagnitude(1.0);

	Period = 2.0;
	*/
	//单次效果
	DurationPolicy = EGameplayEffectDurationType::Instant;


	FGameplayModifierInfo info;

	info.Attribute = FGameplayAttribute(FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)));
	info.ModifierOp = EGameplayModOp::Additive;
	
	//固定值
	//info.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(100.0));

	//CurveTable控制
	/*
	FScalableFloat damageValue = {1.0};
	FCurveTableRowHandle damageCurve;
	static ConstructorHelpers::FObjectFinder<UCurveTable> curveAsset(TEXT("/Game/ActionRPG/DataTable/Damage"));
	damageCurve.CurveTable = curveAsset.Object;
	damageCurve.RowName = FName("Damage");
	damageValue.Curve = damageCurve;

	info.ModifierMagnitude = FGameplayEffectModifierMagnitude(damageValue);
	*/

	FAttributeBasedFloat damageValue;
	damageValue.Coefficient = { 1.2f };
	damageValue.PreMultiplyAdditiveValue = { 1.0f };
	damageValue.PostMultiplyAdditiveValue = { 2.0f };
	damageValue.BackingAttribute = FGameplayEffectAttributeCaptureDefinition(FGameplayAttribute(FindFieldChecked<UProperty>(URPGAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(URPGAttributeSet, Health)))
		, EGameplayEffectAttributeCaptureSource::Source, false);
	FCurveTableRowHandle damageCurve;
	static ConstructorHelpers::FObjectFinder<UCurveTable> curveAsset(TEXT("/Game/ActionRPG/DataTable/Damage"));
	damageCurve.CurveTable = curveAsset.Object;
	damageCurve.RowName = FName("Damage");
	damageValue.AttributeCurve = damageCurve;
	damageValue.AttributeCalculationType = EAttributeBasedFloatCalculationType::AttributeMagnitude;

	info.ModifierMagnitude = damageValue;


	//info.SourceTags=
	//info.TargetTags=
	Modifiers.Add(info);
}
