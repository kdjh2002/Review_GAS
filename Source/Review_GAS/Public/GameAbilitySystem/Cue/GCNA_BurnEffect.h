// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GCNA_BurnEffect.generated.h"

/**
 * 
 */
UCLASS()
class REVIEW_GAS_API AGCNA_BurnEffect : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	AGCNA_BurnEffect();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<class UNiagaraSystem> BurnVFX;

private:
	UPROPERTY()
	TWeakObjectPtr<class UNiagaraComponent> SpawnedVFX;
};
