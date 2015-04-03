// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexGrid.h"


FHexagon::FHexagon():
Transform(),
Type(EHexagonType::HE_Default),
ArrayIndex(-1)
{

}

FHexagon::FHexagon(FTransform & Transform, EHexagonType Type):
Transform(Transform),
Type(Type),
ArrayIndex(-1)
{

}

// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a normal root component
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");


	// Default hexagons component
	Hexagons_default = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Hexagons");
	UStaticMesh* Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Models/Hexagon")).Object;
	Hexagons_default->SetStaticMesh(Mesh);
	Hexagons_default->AttachTo(RootComponent, "Default Hexagons");

	//UpdateGrid();

}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

/*
void AHexGrid::ConstructGrid() {
	Hexagons_default->ClearInstances();

	const int32 _xsize = 50;
	const int32 _ysize = 50;
	const float _xscale = 162.f;
	const float _yscale = 181.f;

	FVector actor_location = GetActorLocation();

	float x, y, z;
	FTransform Instance_transform;
	for (int32 i = 0; i < _xsize; i++) {
		for (int32 j = 0; j < _ysize; j++) {
			y = (j - 0.5f * _ysize) * 0.75 * _yscale;
			x = (i - 0.5f * _xsize) * _xscale + (j % 2) * 0.5f * _xscale;
			z = CalculateZ(x + actor_location.X, y + actor_location.Y, actor_location.Z + 1000, actor_location.Z - 1000) - actor_location.Z;

			Instance_transform.SetLocation(FVector(x, y, z));

			Hexagons_default->AddInstance(Instance_transform);
		}
	}
}
*/


UInstancedStaticMeshComponent* AHexGrid::GetHexMeshComponent(EHexagonType Type) {

	switch (Type) {
	case EHexagonType::HE_Default:
		return Hexagons_default;
	default:
		return nullptr;
	}
}

void AHexGrid::ClearGrid() {
	Hexagons_default->ClearInstances();
	for (int32 i = 0; i < Hexagons.Num(); i++) {
		Hexagons[i].ArrayIndex = -1;
	}
}

void AHexGrid::UpdateGrid() {
	const FVector ActorLoc = this->GetActorLocation();

	FHexagon Hex;
	FVector Loc;
	UInstancedStaticMeshComponent* Comp;
	for (int32 i = 0; i < Hexagons.Num(); i++) {
		Hex = Hexagons[i];

		// If move to ground
		Loc = Hex.Transform.GetLocation();
		Loc.Z = CalculateZ(Loc.X, Loc.Y, ActorLoc.Z + 1000, ActorLoc.Z - 1000) - ActorLoc.Z;
		Hex.Transform.SetLocation(Loc);
		// end if

		Comp = GetHexMeshComponent(Hex.Type);
		if (Comp == nullptr) continue;

		if (Hex.ArrayIndex < 0) {
			Hex.ArrayIndex = Comp->AddInstance(Hex.Transform);
		}
		else {
			Comp->UpdateInstanceTransform(Hex.ArrayIndex, Hex.Transform);
		}

		Hexagons[i] = Hex;
	}
}

void AHexGrid::UpdateHexagon(int32 Index) {
	if (Index < 0) return;

	FHexagon Hex = Hexagons[Index];

	// If move to ground
	const FVector ActorLoc = this->GetActorLocation();
	FVector Loc = Hex.Transform.GetLocation();
	Loc.Z = CalculateZ(Loc.X, Loc.Y, ActorLoc.Z + 1000, ActorLoc.Z - 1000) - ActorLoc.Z;
	Hex.Transform.SetLocation(Loc);
	// end if

	UInstancedStaticMeshComponent* Comp = GetHexMeshComponent(Hex.Type);
	if (Comp == nullptr) return;

	if (Hex.ArrayIndex < 0) {
		Hex.ArrayIndex = Comp->AddInstance(Hex.Transform);
	}
	else {
		Comp->UpdateInstanceTransform(Hex.ArrayIndex, Hex.Transform);
	}

	Hexagons[Index] = Hex;
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


#if WITH_EDITOR

void AHexGrid::PostEditChangeChainProperty(FPropertyChangedChainEvent & Event) {

	if(Event.MemberProperty->GetName().Equals("Hexagons"))
	{

		switch (Event.ChangeType) {

		case EPropertyChangeType::ValueSet:
		case EPropertyChangeType::ArrayAdd: {

			int32 index = Event.GetArrayIndex(TEXT("Hexagons"));
			UE_LOG(LogClass, Log, TEXT("PropertyChain index %d"), index);
			UpdateHexagon(index);
		} break;

		default:
			ClearGrid();
			UpdateGrid();
			break;
		}
	}

	Super::PostEditChangeChainProperty(Event);
}

/*
void AHexGrid::PostEditChangeProperty(FPropertyChangedEvent & Evt) {
	UpdateGrid();
}
*/

void AHexGrid::PostEditMove(bool bFinished) {
	UpdateGrid();
}
#endif

void AHexGrid::AddHexagon(FHexagon& Hexagon) {
	UpdateHexagon(Hexagons.Add(Hexagon));
}

FHexagon AHexGrid::GetHexagon(int32 Index) {
	return Hexagons[Index];
}

void AHexGrid::RemoveHexagon(int32 Index) {
	FHexagon Hex = Hexagons[Index];
	Hexagons.RemoveAt(Index);
	if (Hex.ArrayIndex < 0) return;
	UInstancedStaticMeshComponent* Comp = GetHexMeshComponent(Hex.Type);
	if (Comp == nullptr) return;
	Comp->RemoveInstance(Hex.ArrayIndex);
}

void AHexGrid::EditHexagon(int32 Index, FHexagon& Hexagon) {
	Hexagons[Index] = Hexagon;
	UpdateHexagon(Index);
}

void AHexGrid::ClearHexagons() {
	Hexagons.Empty();
}
