// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "Backman.h"


// Sets default values
ABackman::ABackman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->AttachTo(RootComponent);
	Camera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ABackman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABackman::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ABackman::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &ABackman::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABackman::MoveForward);
	InputComponent->BindAxis("Turn", this, &ABackman::Turn);
}


void ABackman::MoveForward(float Val) {
	if ((Controller != NULL) && (Val != 0.0f)) {
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling()) {
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void ABackman::MoveRight(float Val) {
	if ((Controller != NULL) && (Val != 0.0f)) {
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling()) {
			Rotation.Pitch = 90.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

void ABackman::Turn(float Val) {

}