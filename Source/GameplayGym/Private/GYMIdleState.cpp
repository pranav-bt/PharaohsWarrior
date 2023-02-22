// Fill out your copyright notice in the Description page of Project Settings.


#include "GYMIdleState.h"

void UGYMIdleState::Begin()
{
}

void UGYMIdleState::Update()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("IdleState"));
}

void UGYMIdleState::End()
{
}
