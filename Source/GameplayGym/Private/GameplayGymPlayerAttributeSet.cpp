// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayGymPlayerAttributeSet.h"

//FGameplayAttribute UGameplayGymPlayerAttributeSet::GetHealth()
//{
//	return FGameplayAttribute();
//}
//
//float UGameplayGymPlayerAttributeSet::GetHealthValue() const
//{
//	return 0.0f;
//}
//
//void UGameplayGymPlayerAttributeSet::SetHealth(float NewVal)
//{
//	//GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
//}
//
//void UGameplayGymPlayerAttributeSet::InitHealth(float NewVal)
//{
//}

void UGameplayGymPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Max(GetHealth(), 0.0f));
	}
}
