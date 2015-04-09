// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ViatorumGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VIATORUM_API AViatorumGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
};
