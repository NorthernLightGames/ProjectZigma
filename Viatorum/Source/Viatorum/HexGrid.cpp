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
TraceDistanceDown(2000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a normal root component
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	// Default hexagons component

	UStaticMesh* HexagonMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/HexGrid/Meshes/HexMesh")).Object;

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
/*
void AHexGrid::ClearInstances() {
	for (auto& Elem : HexagonContainers) {
		Elem.Value->ClearInstances();
	}
}
*/

void AHexGrid::UpdateGrid() {
	/*
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
	*/
	const FVector ActorLoc = this->GetActorLocation();

	FVector Loc;
	FTransform transform;
	UInstancedStaticMeshComponent* Comp;
	for (auto& Elem : HexagonContainers) {
		Comp = Elem.Value;
		for (int32 i = 0; i < Comp->GetInstanceCount(); i++) {
			Comp->GetInstanceTransform(i, transform);
			Loc = transform.GetLocation(); 
			if (bStickToGround) {
				Loc.Z = CalculateZ(
					Loc.X + ActorLoc.X,
					Loc.Y + ActorLoc.Y,
					ActorLoc.Z + TraceDistanceUp,
					ActorLoc.Z - TraceDistanceDown
				) - ActorLoc.Z + FlyHeight;
			}
			transform.SetLocation(Loc);
			Comp->UpdateInstanceTransform(i, transform, false);
		}
	}
}

float AHexGrid::CalculateZ(float x, float y, float z_start, float z_end) {

	const float default_ret = (z_end + z_start) / 2.f;

	FVector rayStart(x, y, z_start);
	FVector rayEnd(x, y, z_end);
	UWorld* world = GetWorld();
	if (!world) return default_ret;

	TActorIterator<ALandscape> landscapeIterator(world);
	ALandscape* landscape = *landscapeIterator;
	if (!landscape) return default_ret;

	FCollisionQueryParams collisionParams(FName(TEXT("FoliageClusterPlacementTrace")), true, this);
	collisionParams.bReturnPhysicalMaterial = true;

	FHitResult hit(ForceInit);
	if (landscape->ActorLineTraceSingle(hit, rayStart, rayEnd, ECC_Visibility, collisionParams)) {
		return hit.ImpactPoint.Z;
	}
	else return default_ret;
}

UInstancedStaticMeshComponent* AHexGrid::GetHexagonContainer(EHexagonType Type) {
	return *HexagonContainers.Find((uint8)Type);
}

void AHexGrid::PostInitProperties() {
	UpdateGrid();
	Super::PostInitProperties();
}

#if WITH_EDITOR

void AHexGrid::PostEditChangeProperty(FPropertyChangedEvent & Event) {
	UpdateGrid();
	Super::PostEditChangeProperty(Event);
}

void AHexGrid::PostEditMove(bool bFinished) {
	UpdateGrid();
	Super::PostEditMove(bFinished);
}
#endif