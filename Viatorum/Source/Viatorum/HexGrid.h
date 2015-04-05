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
};

UCLASS()
class VIATORUM_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hexagon Grid")
	TArray<FHexagon> Hexagons;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
		float TraceDistanceDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
		float TraceDistanceUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (DisplayName = "Stick to ground"))
		bool bStickToGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = -10000.f, UIMax = 10000.f))
		float FlyHeight;

	// Sets default values for this actor's properties
	AHexGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitProperties() override;

#if WITH_EDITOR

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent & Event) override;

	virtual void PostEditMove(bool bFinished) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent & Event) override;

#endif

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void AddHexagon(FHexagon Hex);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void GetHexagon(FHexagon& Hex, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void RemoveHexagon(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void EditHexagon(int32 Index, FHexagon Hex);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void ClearHexagons();

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void UpdateGrid();

private:

	float CalculateZ(float X, float Y, float Z_start, float Z_end);

	TMap<uint8, UInstancedStaticMeshComponent*> HexagonContainers;

	void ClearInstances();
	
};
