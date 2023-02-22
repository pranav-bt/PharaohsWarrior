// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SliceAbility.h"
#include "GameplayGymPlayerAttributeSet.h"
#include <GameplayEffectTypes.h>
#include "GameplayGymCharacter.generated.h"

UCLASS(config=Game)
class AGameplayGymCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AGameplayGymCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	/**Attribute Set. */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	const UGameplayGymPlayerAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAcquire;

	//Slicing ability of the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	USliceAbility* SliceAbility;

	virtual void InitializeAttributes();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultEffect;

	virtual void PossessedBy(AController* NewController) override;

	void FSliceAbility();

	void FDashSlice();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Abilities")
	bool DashCooldown = false;
	
	void OnHealthChangedInternal();

	//Magic abilities

	//Magic System Component On Player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MagicSpell, meta = (AllowPrivateAccess = "true"))
	class UMagicSystemComponent* MagicSystemComponent;

	// Spells that the player should have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagicSystem)
	TArray<TSubclassOf<class AMagicSpell>> MagicSpells;

	UFUNCTION(BlueprintImplementableEvent)
	void DealSpellDamageToEnemy(AActor* Enemy, float Damage);

	void CastSpell();

	//HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGameplayGymUserWidget* GameHUD;
	
};

//Example for an enum the FGameplayAbiliyInputBinds may use to map input to ability slots.
//It's very important that this enum is UENUM, because the code will look for UENUM by the given name and crash if the UENUM can't be found. BlueprintType is there so we can use these in blueprints, too. Just in case. Can be neat to define ability packages.
UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	UseAbility1 UMETA(DisplayName = "Use Spell 1"),
	UseAbility3 UMETA(DisplayName = "Use Spell 3"),
	UseAbility4 UMETA(DisplayName = "Use Spell 4"),
	WeaponAbility UMETA(DisplayName = "Use Weapon"), 
};