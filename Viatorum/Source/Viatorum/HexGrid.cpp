// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexGrid.h"
#include "HexagonGridComponent.h"


// Sets default values
AHexGrid::AHexGrid():
XSize(10),
YSize(10),
XScale(200.f),
YScale(FMath::Cos(30.f * PI / 180.f)*200.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Grid = CreateDefaultSubobject<UHexagonGridComponent>("Grid");
	RootComponent = Grid;
}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	UpdateGrid();
}

// Called every frame
void AHexGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHexGrid::UpdateGrid() {
	Grid->Hexagons.Empty();

	const FVector actor_loc = GetActorLocation();
	const int32 _xsize = XSize;
	const int32 _ysize = YSize;
	const float _xscale = XScale;
	const float _yscale = YScale;

	float x;
	float y;
	float z;

	FHexagon Hex;
	for (int32 i = 0; i < _xsize; i++) {
		for (int32 j = 0; j < _ysize; j++) {
			x = (i - 0.5f * _xsize) * 0.75 * _xscale;
			y = (j - 0.5f * _ysize) * _yscale + (i % 2) * 0.5f * _yscale;
			z = CalculateZ(x + actor_loc.X, y + actor_loc.Y, actor_loc.Z + 1000.f, actor_loc.Z - 1000.f) - actor_loc.Z;
			Hex.Location = FVector(x, y, z);
			Grid->Hexagons.Add(Hex);
		}
	}

	Grid->RebuildMesh();
}

float AHexGrid::CalculateZ(float x, float y, float z_start, float z_end) {

	FVector Start(x, y, z_start);
	FVector End(x, y, z_end);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);

	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	FHitResult RV_Hit(ForceInit);

	GetWorld()->LineTraceSingle(
		RV_Hit,
		Start,
		End,
		ECC_WorldStatic,
		RV_TraceParams
		);

	if (RV_Hit.bBlockingHit) {
		return RV_Hit.ImpactPoint.Z;
	}
	else {
		return (z_end + z_start) / 2.f;
	}
}



#ifdef WITH_EDITOR

void AHexGrid::PostEditMove(bool bFinished) {
	UpdateGrid();
}

void AHexGrid::PostEditChangeProperty(FPropertyChangedEvent& evt) {
	UpdateGrid();
}

#endif