// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TestCharacter.generated.h"

UCLASS()
class REVIEW_GAS_API ATestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

	//이 함수를 쓰기 위해서 IAbiliySystemInterface를 상속
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;

	}


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

};
