// Fill out your copyright notice in the Description page of Project Settings.


#include "SliceAbility.h"
#include "../GameplayGymCharacter.h"

void USliceAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sliced"));


	CommitAbility(Handle, ActorInfo, ActivationInfo);
	SetCurrentMontage(SliceMontage);
	
	Cast<AGameplayGymCharacter>(ActorInfo->OwnerActor)->PlayAnimMontage(CurrentMontage);
	EndAbility(Handle,ActorInfo,ActivationInfo, false, false);
}

bool USliceAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	Super::CommitAbility(Handle,ActorInfo,ActivationInfo,OptionalRelevantTags);
	return false;
}

void USliceAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);


	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End-Sliced"));
}

void USliceAbility::SetCurrentMontage(UAnimMontage* InCurrentMontage)
{
	Super::SetCurrentMontage(InCurrentMontage);
}
