// Fill out your copyright notice in the Description page of Project Settings.

#include "Viatorum.h"
#include "HexagonGridComponent.h"


FHexagon::FHexagon(): 
Location(0.f, 0.f, 0.f),
Height(100.f),
Radius(100.f) 
{

}

FHexagon::FHexagon(FVector& Location) :
Location(Location),
Height(100.f),
Radius(100.f) {

}

FHexagon::FHexagon(FVector& Location, float Height) :
Location(Location),
Height(Height),
Radius(100.f) {

}

FHexagon::FHexagon(FVector& Location, float Height, float Radius) :
Location(Location),
Height(Height),
Radius(Radius) {

}

void FHexagon::GetTriangles(TArray<FProceduralMeshTriangle>& TriangleArray) {
	const FVector Top = Location + FVector(0, 0, Height);
	const FVector Bottom = Location;
	

	int32 i = 0;
	int32 j = 6;

	FVector i_vec;
	FVector j_vec;
	FProceduralMeshTriangle Triangle;
	Triangle.Vertex0.Color = FColor::White;
	Triangle.Vertex1.Color = FColor::White;
	Triangle.Vertex2.Color = FColor::White;
	for (i = 0; i <= 6; i++) {

		i_vec = FVector(FMath::Cos(i * 60.f * PI / 180.f), FMath::Sin(i * 60.f * PI / 180.f), 0);

		j_vec = FVector(FMath::Cos(j * 60.f * PI / 180.f), FMath::Sin(j * 60.f * PI / 180.f), 0);

		Triangle.Vertex0.Position = Top;
		Triangle.Vertex0.U = 0.5f;
		Triangle.Vertex0.V = 0.5f;
		Triangle.Vertex1.Position = i_vec * Radius + Top;
		Triangle.Vertex1.U = 0.5f + i_vec.X / 2.f;
		Triangle.Vertex1.V = 0.5f + i_vec.Y / 2.f;
		Triangle.Vertex2.Position = j_vec * Radius + Top;
		Triangle.Vertex2.U = 0.5f + j_vec.X / 2.f;
		Triangle.Vertex2.V = 0.5f + j_vec.Y / 2.f;
		TriangleArray.Add(Triangle);

		Triangle.Vertex0.Position = Bottom;
		Triangle.Vertex0.U = 0.5f;
		Triangle.Vertex0.V = 0.5f;
		Triangle.Vertex1.Position = j_vec * Radius + Bottom;
		Triangle.Vertex1.U = 0.5f + j_vec.X / 2.f;
		Triangle.Vertex1.V = 0.5f + j_vec.Y / 2.f;
		Triangle.Vertex2.Position = i_vec * Radius + Bottom;
		Triangle.Vertex2.U = 0.5f + i_vec.X / 2.f;
		Triangle.Vertex2.V = 0.5f + i_vec.Y / 2.f;
		TriangleArray.Add(Triangle);

		Triangle.Vertex0.Position = j_vec * Radius + Top;
		Triangle.Vertex0.U = 0.f;
		Triangle.Vertex0.V = 0.f;
		Triangle.Vertex1.Position = i_vec * Radius + Top;
		Triangle.Vertex1.U = 1.f;
		Triangle.Vertex1.V = 0.f;
		Triangle.Vertex2.Position = i_vec * Radius + Bottom;
		Triangle.Vertex2.U = 1.f;
		Triangle.Vertex2.V = 1.f;
		TriangleArray.Add(Triangle);

		Triangle.Vertex0.Position = i_vec * Radius + Bottom;
		Triangle.Vertex0.U = 1.f;
		Triangle.Vertex0.V = 1.f;
		Triangle.Vertex1.Position = j_vec * Radius + Bottom;
		Triangle.Vertex1.U = 0.f;
		Triangle.Vertex1.V = 1.f;
		Triangle.Vertex2.Position = j_vec * Radius + Top;
		Triangle.Vertex2.U = 0.f;
		Triangle.Vertex2.V = 0.f;
		TriangleArray.Add(Triangle);

		j = i;
	}
}

void UHexagonGridComponent::RebuildMesh() {
	TArray<FProceduralMeshTriangle> Tris;

	for (int32 i = 0; i < Hexagons.Num(); i++) {
		Hexagons[i].GetTriangles(Tris);
	}

	this->SetProceduralMeshTriangles(Tris);
}


