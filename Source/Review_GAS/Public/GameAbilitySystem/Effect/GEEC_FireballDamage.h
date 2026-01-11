// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_FireballDamage.generated.h"

/**
 * 
 */
UCLASS()
class REVIEW_GAS_API UGEEC_FireballDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_FireballDamage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
private:
	FGameplayTag Tag_DebuffBurn;
};