// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "MrZigma.h"


// Sets default values
AMrZigma::AMrZigma()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	TheVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	TheVisibleComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMrZigma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMrZigma::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	float CurrentScale = TheVisibleComponent->GetComponentScale().X;
	if (bGrowing) {
		// Grow to double size over the course of one second
		CurrentScale += DeltaTime;
	}
	else {
		// Shrink half as fast as we grow
		CurrentScale -= (DeltaTime * 0.5f);
	}
	// Make sure we never drop below our starting size, or increase past double size.
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	TheVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	// Handle movement based on our "MoveX" and "MoveY" axes
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AMrZigma::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &AMrZigma::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMrZigma::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMrZigma::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMrZigma::Move_YAxis);
}

void AMrZigma::Move_XAxis(float AxisValue) {
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMrZigma::Move_YAxis(float AxisValue) {
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMrZigma::StartGrowing() {
	bGrowing = true;
}

void AMrZigma::StopGrowing() {
	bGrowing = false;
}