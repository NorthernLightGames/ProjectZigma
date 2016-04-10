// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "Scientist.h"


// Sets default values
AScientist::AScientist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent *CharacterMovement = this->GetCharacterMovement();

	if (CharacterMovement) {
		CharacterMovement->DefaultLandMovementMode = EMovementMode::MOVE_Walking;
		CharacterMovement->DefaultWaterMovementMode = EMovementMode::MOVE_Falling;
		CharacterMovement->AirControl = 0.7;
		CharacterMovement->SetMovementMode(EMovementMode::MOVE_Falling);
	}


}

// Called when the game starts or when spawned
void AScientist::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScientist::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AScientist::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &AScientist::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AScientist::MoveSide);
	InputComponent->BindAxis("Turn", this, &AScientist::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AScientist::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AScientist::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AScientist::StopJumping);
}

void AScientist::MoveForward(float Val) {
	UCharacterMovementComponent *CharacterMovement = this->GetCharacterMovement();
	if (!CharacterMovement) return;

	if ((Controller != NULL) && (Val != 0.0f)) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void AScientist::MoveSide(float Val) {
	UCharacterMovementComponent *CharacterMovement = this->GetCharacterMovement();
	if (!CharacterMovement) return;

	if ((Controller != NULL) && (Val != 0.0f)) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}