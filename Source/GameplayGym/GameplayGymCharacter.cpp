// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayGymCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "MagicSystemComponent.h"
#include "Public/MyGameplayEffect.h"
#include "SliceAbility.h"

//////////////////////////////////////////////////////////////////////////
// AGameplayGymCharacter

AGameplayGymCharacter::AGameplayGymCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UGameplayGymPlayerAttributeSet>(TEXT("PlayerAttributes"));
	SliceAbility = CreateDefaultSubobject<USliceAbility>(TEXT("Slice"));


	MagicSystemComponent = CreateDefaultSubobject<UMagicSystemComponent>(TEXT("MagicSystem"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGameplayGymCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGameplayGymCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AGameplayGymCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AGameplayGymCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AGameplayGymCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGameplayGymCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGameplayGymCharacter::TouchStopped);

	//Gameplay Abilities
	PlayerInputComponent->BindAction("UseAbility1", IE_Pressed, this, &AGameplayGymCharacter::FSliceAbility);
	PlayerInputComponent->BindAction("UseAbility2", IE_Pressed, this, &AGameplayGymCharacter::FDashSlice);
	PlayerInputComponent->BindAction("Cast", IE_Pressed, this, &AGameplayGymCharacter::CastSpell);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));

	
}

UAbilitySystemComponent* AGameplayGymCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGameplayGymCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultEffect)
	{
		FGameplayEffectContextHandle Effect = AbilitySystemComponent->MakeEffectContext();
		Effect.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultEffect, 1, Effect);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

}

void AGameplayGymCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void AGameplayGymCharacter::FSliceAbility()
{
	if (AbilitySystemComponent)
	{
		const FGameplayTag Combo2 = FGameplayTag::RequestGameplayTag("Effect.Slash.Combo2");
		if (AbilitySystemComponent->HasMatchingGameplayTag(Combo2))
		{
			AbilitySystemComponent->TryActivateAbilityByClass(AbilitiesToAcquire[2]);
			return;
		}
		const FGameplayTag Combo = FGameplayTag::RequestGameplayTag("Effect.Slash.Combo1");
		if (AbilitySystemComponent->HasMatchingGameplayTag(Combo))
		{
			AbilitySystemComponent->TryActivateAbilityByClass(AbilitiesToAcquire[1]);
			return;
		}
		AbilitySystemComponent->TryActivateAbilityByClass(AbilitiesToAcquire[0]);
	}
}

void AGameplayGymCharacter::FDashSlice()
{
	if (AbilitySystemComponent && !DashCooldown)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(AbilitiesToAcquire[3]);
		return;
	}
}

void AGameplayGymCharacter::OnHealthChangedInternal()
{
}

void AGameplayGymCharacter::CastSpell()
{
	MagicSystemComponent->InitializeSpell();
}

void AGameplayGymCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AGameplayGymCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AGameplayGymCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent && AbilitiesToAcquire.Num() > 0)
	{
		for (const TSubclassOf<UGameplayAbility> Ability : AbilitiesToAcquire)
		{
			FGameplayAbilitySpec Spec(Ability);
			AbilitySystemComponent->GiveAbility(Spec);
		}
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();


}

void AGameplayGymCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGameplayGymCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGameplayGymCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	
}

void AGameplayGymCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
