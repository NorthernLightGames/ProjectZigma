// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexGrid.h"


// Sets default values
AHexGrid::AHexGrid():
bStickToGround(true),
FlyHeight(10.f),
TraceDistanceUp(1000.f),
TraceDistanceDown(2000.f),
bGridConstructed(false)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	UStaticMesh* HexagonMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/HexGrid/Meshes/Hexagon")).Object;
	TArray<UMaterialInterface*> Materials;
	UMaterial* Material;

	AddHexagonContainer(EHexagonType::HE_Default, TEXT("Default hexagons"), HexagonMesh, Materials);

	Material = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("/Game/HexGrid/Materials/HexagonAlgaeOvergrownMaterial")).Object;
	Materials.Add(Material);
	AddHexagonContainer(EHexagonType::HE_Algae, TEXT("Algae overgrown hexagons"), HexagonMesh, Materials);
	Materials.Empty();
}

UInstancedStaticMeshComponent* AHexGrid::AddHexagonContainer
(EHexagonType type, FName name, UStaticMesh* Mesh, TArray<UMaterialInterface*>& Materials) {

	UInstancedStaticMeshComponent* HexagonContainer = CreateDefaultSubobject<UInstancedStaticMeshComponent>(name);
	HexagonContainer->SetStaticMesh(Mesh);
	for (int32 i = 0; i < Materials.Num(); i++) {
		HexagonContainer->SetMaterial(i, Materials[i]);
	}
	HexagonContainer->AttachTo(RootComponent, TEXT("Algae overgrown hexagons"));
	HexagonContainers.Add(HexagonContainer);
	return HexagonContainer;
}

void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	UpdateGrid();
}

void AHexGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bGridNeedsUpdate) {
		UpdateGrid();
		bGridNeedsUpdate = false;
	}
}

void AHexGrid::UpdateGrid() {
	const FVector ActorLoc = this->GetActorLocation();

	FVector Loc;
	FTransform transform;
	UInstancedStaticMeshComponent* Comp;
	for (int32 i = 0; i < GetHexagonContainerCount(); i++) {
		Comp = GetHexagonContainer(i);
		for (int32 i = 0; i < Comp->GetInstanceCount(); i++) {
			Comp->GetInstanceTransform(i, transform, true);

			if (bStickToGround) {
				Loc = transform.GetLocation();
				Loc.Z = CalculateZ(
					Loc.X,
					Loc.Y,
					ActorLoc.Z + TraceDistanceUp,
					ActorLoc.Z - TraceDistanceDown
				) + FlyHeight;
				transform.SetLocation(Loc);
			}

			Comp->UpdateInstanceTransform(i, transform, true);
		}
	}
}

float AHexGrid::CalculateZ(float x, float y, float z_start, float z_end) {

	const float default_ret = (z_end + z_start) / 2.f;

	FVector rayStart(x, y, z_start);
	FVector rayEnd(x, y, z_end);
	UWorld* world = GetWorld();
	if (!world) return default_ret;
	if (!world->IsValidLowLevel()) return default_ret;

	TActorIterator<ALandscape> landscapeIterator(world);
	if (!landscapeIterator) return default_ret;
	ALandscape* landscape = *landscapeIterator;
	if (!landscape) return default_ret;
	if (!landscape->IsValidLowLevel()) return default_ret;

	FCollisionQueryParams collisionParams(FName(TEXT("FoliageClusterPlacementTrace")), true, this);
	collisionParams.bReturnPhysicalMaterial = true;

	FHitResult hit(ForceInit);
	if (landscape->ActorLineTraceSingle(hit, rayStart, rayEnd, ECC_Visibility, collisionParams)) {
		return hit.ImpactPoint.Z;
	}
	else return default_ret;
}

void AHexGrid::PostInitProperties() {
	Super::PostInitProperties();
	if (!bGridConstructed) {
		ConstructGrid();
		bGridConstructed = true;
	}
	bGridNeedsUpdate = true;
}

UInstancedStaticMeshComponent* AHexGrid::GetHexagonContainerFromType(EHexagonType Type) {
	return HexagonContainers[(int32)((uint8)Type)];
}

UInstancedStaticMeshComponent* AHexGrid::GetHexagonContainer(int32 Index) {
	return HexagonContainers[Index];
}

int32 AHexGrid::GetHexagonContainerCount() {
	return HexagonContainers.Num();
}

void AHexGrid::ConstructGrid() {

}

#if WITH_EDITOR

void AHexGrid::PostEditChangeProperty(FPropertyChangedEvent & Event) {
	Super::PostEditChangeProperty(Event);
	UpdateGrid();
}

void AHexGrid::PostEditMove(bool bFinished) {
	Super::PostEditMove(bFinished);
	UpdateGrid();
}
#endif