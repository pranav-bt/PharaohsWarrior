// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API UMyGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMyGameplayEffect> ActualClass;
	
};
