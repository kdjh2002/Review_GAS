// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TestCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameAbilitySystem/AttributeSet/PlayerAttributeSet.h"
#include "GameAbilitySystem/AttributeSet/EnemyAttributeSet.h"
#include "EnhancedInputComponent.h"

AGasCharacter::AGasCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// 요구사항에 맞춰 두 AttributeSet 모두 생성 (하나의 캐릭터 클래스로 둘 다 쓰기 위해)
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	HealthWidgetComp->SetupAttachment(RootComponent);
}

void AGasCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// 기본 스탯 적용
		if (DefaultAttributeEffect)
		{
			AbilitySystemComponent->ApplyGameplayEffectToSelf(DefaultAttributeEffect.GetDefaultObject(), 1.0f, AbilitySystemComponent->MakeEffectContext());
		}

		// 파이어볼 어빌리티 부여 (플레이어인 경우만 의미 있음)
		if (FireballAbilityClass)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireballAbilityClass, 1, 0));
		}

		// 값 변경 감지 (UI 연결)
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute()).AddUObject(this, &AGasCharacter::OnManaChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute()).AddUObject(this, &AGasCharacter::OnHealthChange);
	}
}

void AGasCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Fire)
		{
			EnhancedInput->BindAction(IA_Fire, ETriggerEvent::Started, this, &AGasCharacter::OnFireballInput);
		}
	}
}

void AGasCharacter::OnFireballInput()
{
	if (AbilitySystemComponent && FireballAbilityClass)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(FireballAbilityClass);
	}
}

void AGasCharacter::OnManaChange(const FOnAttributeChangeData& InData)
{
	// 블루프린트 위젯 업데이트 로직 (HUD)
}

void AGasCharacter::OnHealthChange(const FOnAttributeChangeData& InData)
{
	// 블루프린트 위젯 업데이트 로직 (Enemy HP Bar)
}

