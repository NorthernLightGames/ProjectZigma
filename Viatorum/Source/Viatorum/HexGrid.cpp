// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexGrid.h"


FHexagon::FHexagon():
Transform(),
Type(EHexagonType::HE_Default)
{

}

FHexagon::FHexagon(FTransform & Transform, EHexagonType Type):
Transform(Transform),
Type(Type)
{

}

// Sets default values
AHexGrid::AHexGrid():
bStickToGround(true),
FlyHeight(10.f),
TraceDistanceUp(1000.f),
TraceDistanceDown(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a normal root component
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");


	// Default hexagons component

	UStaticMesh* HexagonMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Models/HexMesh")).Object;

	UInstancedStaticMeshComponent* HexagonContainer;

	// For each in EHexagonType
	HexagonContainer = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Default Hexagons");
	HexagonContainer->SetStaticMesh(HexagonMesh);
	HexagonContainer->AttachTo(RootComponent, TEXT("Default Hexagons"));
	HexagonContainers.Add((uint8)EHexagonType::HE_Default, HexagonContainer);
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

void AHexGrid::ClearInstances() {
	for (auto& Elem : HexagonContainers) {
		Elem.Value->ClearInstances();
	}
}

void AHexGrid::UpdateGrid() {
	ClearInstances();

	const FVector ActorLoc = this->GetActorLocation();

	FHexagon Hex;
	FVector Loc;
	UInstancedStaticMeshComponent* Comp;
	for (int32 i = 0; i < Hexagons.Num(); i++) {
		Hex = Hexagons[i];

		// If move to ground
		Loc = Hex.Transform.GetLocation();
		if (bStickToGround) {
			Loc.Z = CalculateZ(
				Loc.X + ActorLoc.X, 
				Loc.Y + ActorLoc.Y, 
				ActorLoc.Z + TraceDistanceUp, 
				ActorLoc.Z - TraceDistanceDown
			) - ActorLoc.Z + FlyHeight;
		}
		Hex.Transform.SetLocation(Loc);
		// end if

		Comp = *HexagonContainers.Find((uint8)Hex.Type);
		if (Comp == nullptr) continue;

		Comp->AddInstance(Hex.Transform);

		Hexagons[i] = Hex;
	}
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

void AHexGrid::AddHexagon(FHexagon Hexagon) {
	Hexagons.Add(Hexagon);
}

void AHexGrid::GetHexagon(FHexagon& Hex, int32 Index) {
	Hex = Hexagons[Index];
}

void AHexGrid::RemoveHexagon(int32 Index) {
	Hexagons.RemoveAt(Index);
}

void AHexGrid::EditHexagon(int32 Index, FHexagon Hexagon) {
	Hexagons[Index] = Hexagon;
}

void AHexGrid::ClearHexagons() {
	Hexagons.Empty();
}

void AHexGrid::PostInitProperties() {
	Super::PostInitProperties();
	UpdateGrid();
}

#if WITH_EDITOR

void AHexGrid::PostEditChangeChainProperty(FPropertyChangedChainEvent & Event) {
	UpdateGrid();
	Super::PostEditChangeChainProperty(Event);
}

void AHexGrid::PostEditChangeProperty(FPropertyChangedEvent & Event) {
	UpdateGrid();
	Super::PostEditChangeProperty(Event);
}

void AHexGrid::PostEditMove(bool bFinished) {
	UpdateGrid();
	Super::PostEditMove(bFinished);
}
#endif