// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "Hexagons.h"


// Sets default values
AHexagons::AHexagons():
bStickToGround(true),
FlyHeight(10.f),
TraceDistanceUp(1000.f),
TraceDistanceDown(2000.f),
Scale(200.f) {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	UStaticMesh* HexagonMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Sigma/HexGrid/Meshes/Hexagon")).Object;
	TArray<UMaterialInterface*> Materials;
	UMaterial* Material;

	AddHexagonContainer(EHexagonType::HE_Default, TEXT("Default hexagons"), HexagonMesh, Materials);

	Material = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("/Game/Sigma/HexGrid/Materials/HexagonAlgaeOvergrownMaterial")).Object;
	Materials.Add(Material);
	AddHexagonContainer(EHexagonType::HE_Algae, TEXT("Algae overgrown hexagons"), HexagonMesh, Materials);
	Materials.Empty();
}

UInstancedStaticMeshComponent* AHexagons::AddHexagonContainer
(EHexagonType type, FName name, UStaticMesh* Mesh, TArray<UMaterialInterface*>& Materials) {

	UInstancedStaticMeshComponent* HexagonContainer = CreateDefaultSubobject<UInstancedStaticMeshComponent>(name);
	HexagonContainer->SetStaticMesh(Mesh);
	for (int32 i = 0; i < Materials.Num(); i++) {
		HexagonContainer->SetMaterial(i, Materials[i]);
	}
	HexagonContainer->AttachTo(RootComponent, name);
	HContainers.Add(HexagonContainer);
	return HexagonContainer;
}

void AHexagons::BeginPlay() {
	Super::BeginPlay();
}

void AHexagons::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AHexagons::UpdateGrid() {

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

float AHexagons::CalculateZ(float x, float y, float z_start, float z_end) {

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

UInstancedStaticMeshComponent* AHexagons::GetHexagonContainerFromType(EHexagonType Type) {
	return HContainers[(int32)((uint8)Type)];
}

UInstancedStaticMeshComponent* AHexagons::GetHexagonContainer(int32 Index) {
	return HContainers[Index];
}

int32 AHexagons::GetHexagonContainerCount() {
	return HContainers.Num();
}

void AHexagons::SetHexagons(const TArray<FHexagon>& Hexagons) {
	UInstancedStaticMeshComponent* Comp;
	FVector Location(0, 0, 0);
	FHexagon Hex;

	// Clear old hexagons
	for (int32 i = 0; i < GetHexagonContainerCount(); i++) {
		Comp = GetHexagonContainer(i);
		if (!Comp) continue;
		Comp->ClearInstances();
	}

	// Add new hexagons
	for (int32 i = 0; i < Hexagons.Num(); i++) {
		Hex = Hexagons[i];
		Comp = GetHexagonContainerFromType(Hex.Type);
		if (Comp == nullptr) continue;

		HexToSpace(Hex.X, Hex.Y, Location);

		Comp->AddInstance(FTransform(Location));
	}

	UpdateGrid();
}

void AHexagons::HexToSpace(int32 X, int32 Y, FVector& result) {
	const float ScaleY = Scale;
	const float ScaleX = FMath::Sin(60.f * (PI / 180.f)) * Scale;
	result.X = (X + (Y % 2)*0.5)*ScaleX;
	result.Y = (Y * 0.75)*ScaleY;
}