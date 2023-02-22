// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GYMCharacterState.h"
#include "GYMAttackState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API UGYMAttackState : public UGYMCharacterState
{
	GENERATED_BODY()
public:


	virtual void Begin();
	virtual void Update();
	virtual void End();
};
