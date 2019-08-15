#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class ACTIONRPG_API UDamageMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UDamageMagnitudeCalculation();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
