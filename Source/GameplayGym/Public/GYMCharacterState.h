// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GYMCharacterState.generated.h"


class UGYMAttackState;
class UGYMIdleState;
class UGYMSlashState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYGYM_API UGYMCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGYMCharacterState();

	enum PlayerState
	{
		EIdleState,
		EAttackState,
		ESlashState
	};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	PlayerState CurrentPlayerState;

	UGYMIdleState* IdlePlayerState;
	UGYMAttackState* AttackPlayerState;
	UGYMSlashState* SlashPlayerState;
};
