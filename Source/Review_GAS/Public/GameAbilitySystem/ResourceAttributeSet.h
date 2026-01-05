// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ResourceAttributeSet.generated.h"

/**
 * 
 */

//어트리뷰트 Getter/Setter/Initializer를 쉽게 만들어주는 매크로
//언리얼Gas 시작할떄 무조건 넣기
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 



UCLASS()
class REVIEW_GAS_API UResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UResourceAttributeSet();

	//어트리뷰트 데이터 //전부 Float
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UResourceAttributeSet, Health)

};
