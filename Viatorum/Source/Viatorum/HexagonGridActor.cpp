// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexagonGridActor.h"


// Sets default values
AHexagonGridActor::AHexagonGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UHexagonGrid* hexagonGrid = NewNamedObject<UHexagonGrid>(this, FName("Grid"));
	RootComponent = hexagonGrid;
}

// Called when the game starts or when spawned
void AHexagonGridActor::BeginPlay()
{
	Super::BeginPlay();
	RootComponent->RegisterComponent();
}

// Called every frame
void AHexagonGridActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

