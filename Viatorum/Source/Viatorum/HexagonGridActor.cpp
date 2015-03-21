// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexagonGridActor.h"


// Sets default values
AHexagonGridActor::AHexagonGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Grid = CreateDefaultSubobject<UHexagonGrid>(FName("RootComponent"));
	RootComponent = Grid;
}

// Called when the game starts or when spawned
void AHexagonGridActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHexagonGridActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

