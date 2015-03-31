// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hexagon.h"
#include "HexGrid.generated.h"


UCLASS()
class VIATORUM_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AHexGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UInstancedStaticMeshComponent* GetHexagonComponentByType(EHexagonType Type);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;

	virtual void PostEditMove(bool bFinished) override;
#endif

private:

	float CalculateZ(float X, float Y, float Z_start, float Z_end);

	void UpdateGrid();

	UInstancedStaticMeshComponent* Hexagons_default;
	
};
