// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SliceAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API USliceAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	/** Executes PreActivate and ActivateAbility */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	//Montages
	/** Active montage being played by this ability */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability_Montage")
	class UAnimMontage* SliceMontage;

	//Montage
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage) override;
};
