// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellAnimNotify.h"
#include "MagicSystemComponent.h"
#include "../GameplayGymCharacter.h"

void USpellAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && Cast<AGameplayGymCharacter>(MeshComp->GetOwner()))
	{
		Cast<AGameplayGymCharacter>(MeshComp->GetOwner())->MagicSystemComponent->CastSpell();
	}
}
