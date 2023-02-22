// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayGymUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API UGameplayGymUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cooldown")
	void ApplyCooldown(class UMagicSystemComponent* MagicSystem, int32 PowerIndex, float CooldownTimer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cooldown")
	void ApplyDashCooldown(float CooldownTimer);
};
