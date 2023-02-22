// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectExtension.h"
#include "GameplayGymPlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API UGameplayGymPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	/** Sample "Health" Attribute, publicly accessible */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//~ Helper functions for "Health" attributes
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UGameplayGymPlayerAttributeSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	//~ ... Helper functions for other Gameplay Attributes here ...
};
