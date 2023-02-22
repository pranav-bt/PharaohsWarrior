// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "MagicSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYGYM_API UMagicSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagicSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateMana(int32 Manareceived);

	//Add all the montages that the player will use throughout the game for spells. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagicSystem)
	TArray<class UAnimMontage*> MagicSpellMontages;

	//Only add magic spells with which the player should start the game. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagicSystem)
	TArray<TSubclassOf<class AMagicSpell>> MagicSpells;

	TArray<int32> SpellCooldowns;

	int32 Mana = 100;

	bool HasEnoughMana();

	void ConsumeMana(int32 ManaToConsume);

	UFUNCTION(BlueprintCallable)
	void ResetCooldown(int32 SpellIndex);

	void InitializeSpell();

	void CastSpell();

	bool CanCast = true;

	void AddNewSpell(TSubclassOf<class AMagicSpell> SpellToAdd);

	void ChangeActiveSpell(int32 Index);

	int32 ActiveSpellIndex = 0;

	class AGameplayGymCharacter* PlayerCharacter;

	// Audio Component
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	USoundCue* GetNewSpellSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		USoundCue* NoManaSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		USoundCue* KillSFX;
};
