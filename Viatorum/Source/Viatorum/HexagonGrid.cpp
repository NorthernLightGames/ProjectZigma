// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexagonGrid.h"


// Sets default values for this component's properties
UHexagonGrid::UHexagonGrid()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CreateHexagons();
}


// Called when the game starts
void UHexagonGrid::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	RegisterHexagons();
}


// Called every frame
void UHexagonGrid::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UHexagonGrid::ConstructGrid() {
	CreateHexagons();
	RegisterHexagons();
}

void UHexagonGrid::RegisterHexagons() {
	UHexagon* hexagon;
	for (int32 i = 0; i < Hexagons.Num(); i++) {
		hexagon = Hexagons[i];
		hexagon->AttachParent = this;
		hexagon->RegisterComponent();
	}
}

void UHexagonGrid::CreateHexagons() {
	Hexagons.Empty();

	int32 index = 0;

	FString name;
	UHexagon* hexagon;

	float x, y, z;
	for (int32 i = 0; i < 10; i++)
	for (int32 j = 0; j < 10; j++) {

		y = ((float)j - 0.5f)*45.f*1.5f;
		x = ((float)i - 0.5f)*80.f + (j % 2)*40.f;

		name = FString::Printf(TEXT("Hexagon Mesh %i"), index);

		hexagon = NewNamedObject<UHexagon>(this, FName(*name));

		z = GetZPosition(x, y);

		hexagon->SetRelativeLocation(FVector(x, y, 0.f));
		hexagon->AttachTo(this, FName(*name), EAttachLocation::KeepRelativeOffset);

		Hexagons.Add(hexagon);

		index++;
	}
}

float UHexagonGrid::GetZPosition(float x, float y) {
	return 0;
}