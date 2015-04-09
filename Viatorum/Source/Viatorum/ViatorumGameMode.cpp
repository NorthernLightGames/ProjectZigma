// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "ViatorumGameMode.h"



void AViatorumGameMode::StartPlay() {
	Super::StartPlay();

	StartMatch();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("VIATORUM :D :D :D"));
	}
}