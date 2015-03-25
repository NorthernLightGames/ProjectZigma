// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexagonGrid.h"


AHexagonGrid::AHexagonGrid():
XSize(10), YSize(10), XScale(80.5f), YScale(91.f), 
Mesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Models/Hexagon")).Object) {
	PrimaryActorTick.bCanEverTick = true;
	this->bCanBeDamaged = false;
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	this->SetRootComponent(root);
}

void AHexagonGrid::BeginPlay(){
	Super::BeginPlay();
}

void AHexagonGrid::Tick( float DeltaTime ){
	Super::Tick(DeltaTime);
}

void AHexagonGrid::OnConstruction(const FTransform& Transform) {
	ConstructGrid();
}

// This method supposes that all grid components has been created
void AHexagonGrid::ComputeLocations() {

	// Store properties as local constants
	const int32 _xsize = XSize;
	const int32 _ysize = YSize;
	const float _xscale = XScale;
	const float _yscale = YScale;

	// Location of root component in world space
	FVector actor_location = GetActorLocation();

	float x;
	float y;
	float z;

	FVector element_location;
	USceneComponent * element;
	for (int32 i = 0; i < _xsize; i++) {
		for (int32 j = 0; j < _ysize; j++) {

			element = RootComponent->GetChildComponent((i*_ysize) + j);
			if (element == nullptr) continue;

			y = ((j - 0.5f * _ysize) * 0.75 * _yscale);
			x = ((i - 0.5f * _xsize) * _xscale + (j % 2) * 0.5f * _xscale);
			z = CalculateZ(x + actor_location.Y, y + actor_location.X, actor_location.Z + 1000, actor_location.Z - 1000) - actor_location.Z;

			element_location = FVector(x, y, z);

			element->SetRelativeLocation(element_location);
		}
	}
}

void AHexagonGrid::ConstructGrid() {

	// Clear grid
	for (int32 i = 0; i < RootComponent->GetNumChildrenComponents(); i++) {
		RootComponent->GetChildComponent(i)->DestroyComponent();
	}

	// Store properties as local constants
	const int32 _xsize = XSize;
	const int32 _ysize = YSize;
	const float _xscale = XScale;
	const float _yscale = YScale;

	// Location of root component in world space
	FVector actor_location = GetActorLocation();

	// The mesh
	UStaticMesh* mesh = Mesh;

	float x;
	float y;
	float z;
	FVector element_location;
	UStaticMeshComponent * element;
	for (int32 i = 0; i < _xsize; i++) {
		for (int32 j = 0; j < _ysize; j++) {

			y = (j - 0.5f * _ysize) * 0.75 * _yscale;
			x = (i - 0.5f * _xsize) * _xscale + (j % 2) * 0.5f * _xscale;
			z = CalculateZ(x + actor_location.X, y + actor_location.Y, actor_location.Z + 1000, actor_location.Z - 1000);

			element_location = FVector(x, y, z - actor_location.Z);

			element = NewObject<UStaticMeshComponent> (this);
			element->SetRelativeLocation(element_location);
			element->SetStaticMesh(mesh);
			element->AttachTo(this->RootComponent);
			element->RegisterComponent();
		}
	}
}

float AHexagonGrid::CalculateZ(float x, float y, float z_start, float z_end) {

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
void AHexagonGrid::PostEditChangeProperty(FPropertyChangedEvent& evt) {
	/**
	FName PropertyName = (evt.Property != NULL) ? evt.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AHexagonGrid, XSize) || PropertyName == GET_MEMBER_NAME_CHECKED(AHexagonGrid, YSize))) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ConstructGrid() called"));
		ConstructGrid();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ComputeLocations() called"));
		ComputeLocations();
	}
	*/
	ConstructGrid();
}
#endif