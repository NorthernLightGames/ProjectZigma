// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Backman.generated.h"

UCLASS()
class VIATORUM_API ABackman : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABackman();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float Val);

	void MoveRight(float Val);

	void BeginJump();

	void EndJump();

	UCameraComponent* Camera;
};
