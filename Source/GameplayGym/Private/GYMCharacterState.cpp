// Fill out your copyright notice in the Description page of Project Settings.


#include "GYMCharacterState.h"
#include "GYMIdleState.h"
#include "GYMAttackState.h"
#include "GYMSlashState.h"
// Sets default values for this component's properties
UGYMCharacterState::UGYMCharacterState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UGYMCharacterState::BeginPlay()
{
	Super::BeginPlay();
	IdlePlayerState = NewObject<UGYMIdleState>(this);
	AttackPlayerState = NewObject<UGYMAttackState>(this);
	SlashPlayerState = NewObject<UGYMSlashState>(this);
	CurrentPlayerState = ESlashState;
}


// Called every frame
void UGYMCharacterState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (CurrentPlayerState)
	{
	case PlayerState::EIdleState:
		IdlePlayerState->Update();
	case PlayerState::EAttackState:
		AttackPlayerState->Update();
	case PlayerState::ESlashState:
		SlashPlayerState->Update();
	}

	
}

