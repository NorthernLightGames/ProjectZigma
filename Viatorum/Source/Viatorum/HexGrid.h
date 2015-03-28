// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HexagonGridComponent.h"
#include "HexGrid.generated.h"

UCLASS()
class VIATORUM_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Config",
			  meta = (DisplayName = "X size", ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 XSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Config",
			  meta = (DisplayName = "Y size", ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 YSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Config",
			  meta = (DisplayName = "X scale", ClampMin = "1", ClampMax = "1000", UIMin = "1", UIMax = "1000"))
	float XScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Config",
			  meta = (DisplayName = "Y scale", ClampMin = "1", ClampMax = "1000", UIMin = "1", UIMax = "1000"))
	float YScale;

	// Sets default values for this actor's properties
	AHexGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

#ifdef WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditMove(bool bFinished) override;
#endif

private:

	float CalculateZ(float x, float y, float z_start, float z_end);

	void UpdateGrid();

	UHexagonGridComponent* Grid;
};
