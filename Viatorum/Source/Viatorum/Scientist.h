// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Scientist.generated.h"

UCLASS()
class VIATORUM_API AScientist : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AScientist();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float Val);
	void MoveSide(float Val);
	
};
