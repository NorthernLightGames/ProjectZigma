// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "Hexagon.h"


// Sets default values for this component's properties
UHexagon::UHexagon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	UStaticMesh* HexagonMesh = nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshOb(TEXT("/Game/Models/Hexagon"));
	if (MeshOb.Succeeded()) {
		HexagonMesh = MeshOb.Object;
	}

	Mesh = NewNamedObject<UStaticMeshComponent>(this, FName("Mesh"));
	Mesh->AttachTo(this, NAME_None, EAttachLocation::KeepRelativeOffset);
	Mesh->SetStaticMesh(HexagonMesh);
}


// Called when the game starts
void UHexagon::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	Mesh->AttachParent = this;
	Mesh->RegisterComponent();
}


// Called every frame
void UHexagon::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

