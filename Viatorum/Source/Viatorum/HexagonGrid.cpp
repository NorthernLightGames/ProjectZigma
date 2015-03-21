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
}


// Called every frame
void UHexagonGrid::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UHexagonGrid::CreateHexagons() {

	int32 index = 0;

	FString name;
	UHexagon* hexagon;
	float x;
	float y;
	for (int32 i = 0; i < 10; i++)
	for (int32 j = 0; j < 10; j++) {

		y = ((float)j - 0.5f)*45.f*1.5f;
		x = ((float)i - 0.5f)*80.f + (j % 2)*40.f;

		name = FString::Printf(TEXT("Hexagon Mesh %i"), index);

		hexagon = CreateDefaultSubobject<UHexagon>(FName(*name));

		hexagon->AttachTo(this, FName(*name));

		hexagon->SetRelativeLocation(FVector(x, y, 0.f));

		index++;
	}
}