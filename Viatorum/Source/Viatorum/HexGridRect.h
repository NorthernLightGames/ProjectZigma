// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexGrid.h"
#include "HexGridRect.generated.h"

/**
 * 
 */
UCLASS()
class VIATORUM_API AHexGridRect : public AHexGrid
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid Rect", meta = (ClampMax = 1000, ClampMin = 0))
	int32 XSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid Rect", meta = (ClampMax = 1000, ClampMin = 0))
	int32 YSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid Rect", meta = (ClampMax = 1000.f, ClampMin = 1.f))
	float XScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid Rect", meta = (ClampMax = 1000.f, ClampMin = 1.f))
	float YScale;
	
	AHexGridRect();

#ifdef WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent & Event) override;
#endif

protected:

	virtual void ConstructGrid() override;
};
