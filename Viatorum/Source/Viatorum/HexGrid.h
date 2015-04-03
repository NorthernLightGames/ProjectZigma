// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"


UENUM(BlueprintType)
enum class EHexagonType : uint8 {
	HE_Default UMETA(DisplayName = "Default")
	// Add more later on
};

USTRUCT(BlueprintType)
struct FHexagon {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	EHexagonType Type;

	FHexagon();

	FHexagon(FTransform & Transform, EHexagonType Type);

private:

	UPROPERTY()
	int32 ArrayIndex;

	friend class AHexGrid;
};

UCLASS()
class VIATORUM_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HexGrid")
		TArray<FHexagon> Hexagons;

public:

	// Sets default values for this actor's properties
	AHexGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void AddHexagon(FHexagon& Hex);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	FHexagon GetHexagon(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void RemoveHexagon(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void EditHexagon(int32 Index, FHexagon& Hex);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void ClearHexagons();

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent & Event) override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent & Event) override;

	virtual void PostEditMove(bool bFinished) override;
#endif

private:

	void ClearGrid();

	void UpdateGrid();

	void UpdateHexagon(int32 Index);

	float CalculateZ(float X, float Y, float Z_start, float Z_end);

	UInstancedStaticMeshComponent* GetHexMeshComponent(EHexagonType Type);

	UInstancedStaticMeshComponent* Hexagons_default;
	
};
