// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "HexagonGridComponent.generated.h"

USTRUCT(BlueprintType)
struct FHexagon {
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	float Radius;

	FHexagon();

	FHexagon(FVector& Location);

	FHexagon(FVector& Location, float Height);
	
	FHexagon(FVector& Location, float Height, float Radius);

	void GetTriangles(TArray<FProceduralMeshTriangle>& TriangleArray);
};

/**
 * 
 */
UCLASS()
class VIATORUM_API UHexagonGridComponent : 
	public UProceduralMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "HexagonGrid")
	void RebuildMesh();

	TArray<FHexagon> Hexagons;
};
