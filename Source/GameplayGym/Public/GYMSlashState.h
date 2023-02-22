// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GYMAttackState.h"
#include "GYMSlashState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYGYM_API UGYMSlashState : public UGYMAttackState
{
	GENERATED_BODY()
	

public:
	virtual void Begin() override;
	virtual void Update() override;
	virtual void End() override;
};
