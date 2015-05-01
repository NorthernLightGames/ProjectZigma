// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Landscape/Classes/Landscape.h"
#include "HexGrid.generated.h"


/*
 * Hexagon type enum
 */
UENUM(BlueprintType)
enum class EHexType : uint8 {
	HTE_Default UMETA(DisplayName = "Default"),
	HTE_Algae UMETA(DisplayName = "Algae overgrown")

};

/*
 * Hexagon grid
 */
UCLASS()
class VIATORUM_API AHexGrid : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
	float TraceDistanceDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
	float TraceDistanceUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (DisplayName = "Stick to ground"))
	bool bStickToGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon Grid", meta = (UIMin = -10000.f, UIMax = 10000.f))
	float FlyHeight;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Hexagon Grid" )
	TArray<UInstancedStaticMeshComponent*> HexagonContainers;

	UPROPERTY()
	bool bGridConstructed;

	bool bGridNeedsUpdate;

public:

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void UpdateGrid();

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid", meta = (DisplayName = "Get Hexagon Container by type"))
	UInstancedStaticMeshComponent* GetHexagonContainerFromType(EHexType Type);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid", meta = (DisplayName = "Get Hexagon Container"))
	UInstancedStaticMeshComponent* GetHexagonContainer(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid", meta = (DisplayName = "Get number of Hexagon Containers"))
	int32 GetHexagonContainerCount();

	AHexGrid();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditUndo() override;
	virtual void PostEditMove(bool bFinished) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;
#endif

protected:

	virtual void ConstructGrid();

private:

	UInstancedStaticMeshComponent* AddHexagonContainer(EHexType type, FName name, UStaticMesh* Mesh, TArray<UMaterialInterface*>& Materials);
	float CalculateZ(float X, float Y, float Z_start, float Z_end);
};
