// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexGridRect.h"




AHexGridRect::AHexGridRect():
XSize(20),
YSize(20),
XScale(173.f),
YScale(200.f) {
	GenerateGrid();
	UpdateGrid();
}

void AHexGridRect::GenerateGrid() {

	const float XScale = this->XScale;
	const float YScale = this->YScale;
	const int32 XSize = this->XSize;
	const int32 YSize = this->YSize;

	UInstancedStaticMeshComponent* Comp = GetHexagonContainer(EHexagonType::HE_Default);
	if (!Comp) return;
	Comp->ClearInstances();

	float x, y;
	FTransform transform;
	FVector vector;
	for (int32 i = 0; i < XSize; i++) {
		for (int32 j = 0; j < YSize; j++) {
			x = (((float)i - 0.5f*XSize) + (j % 2)*0.5f)*XScale;
			y = ((float)j - 0.5f*YSize) * 0.75f * YScale;
			vector = FVector(x, y, 0.f);
			transform.SetLocation(vector);
			Comp->AddInstance(transform);
		}
	}
}

#ifdef WITH_EDITOR

void AHexGridRect::PostEditChangeProperty(FPropertyChangedEvent & Event) {
	GenerateGrid();
	Super::PostEditChangeProperty(Event);
}

#endif