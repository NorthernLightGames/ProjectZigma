// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Hexagon.h"
#include "HexagonGrid.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIATORUM_API UHexagonGrid : public USceneComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UHexagonGrid();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "Grid Config")
	void ConstructGrid();

	UPROPERTY()
		TArray<UHexagon*> Hexagons;
	
private:

	void RegisterHexagons();

	void CreateHexagons();
};
