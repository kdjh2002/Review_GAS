// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Effect/GEEC_FireballDamage.h"
#include "GameAbilitySystem/AttributeSet/EnemyAttributeSet.h" // 적의 체력을 깎아야 하므로 EnemyAttributeSet 참조

struct FFireballDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	FFireballDamageStatics()
	{
		// Target(적)의 EnemyAttributeSet에 있는 Health를 캡처
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);
	}
};

static FFireballDamageStatics& FireballDamageStatics()
{
	static FFireballDamageStatics Statics;
	return Statics;
}

UGEEC_FireballDamage::UGEEC_FireballDamage()
{
	RelevantAttributesToCapture.Add(FireballDamageStatics().HealthDef);
	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));
}

void UGEEC_FireballDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (TargetASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

		float Damage = 10.0f; // 기본 데미지 10

		if (TargetTags && TargetTags->HasTag(Tag_DebuffBurn))
		{
			Damage *= 2.0f; // Burn 상태면 2배
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(FireballDamageStatics().HealthProperty, EGameplayModOp::Additive, -Damage)
			);
		}
	}
}