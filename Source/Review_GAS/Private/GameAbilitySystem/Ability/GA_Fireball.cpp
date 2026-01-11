// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Ability/GA_Fireball.h"
#include "GameFramework/Character.h"

UGA_Fireball::UGA_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character && ProjectileClass)
	{
		FVector SpawnLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 100.0f;
		FRotator SpawnRotation = Character->GetActorRotation();
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}