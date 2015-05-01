// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Landscape/Classes/Landscape.h"
#include "Hexagons.generated.h"


/*
 Hexagon type
*/
UENUM(BlueprintType)
enum class EHexagonType : uint8 {
	HE_Default UMETA(DisplayName = "Default"),
	HE_Algae UMETA(DisplayName = "Algae overgrown")

};

/*
 Hexagon
*/
USTRUCT(BlueprintType)
struct FHexagon {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon", meta = (DisplayName = "X"))
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon", meta = (DisplayName = "Y"))
	int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	TEnumAsByte<EHexagonType> Type;
};

UCLASS()
class VIATORUM_API AHexagons : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> HContainers;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagons", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
	float TraceDistanceDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagons", meta = (UIMin = 100.f, UIMax = 100000.f, ClampMax = 10000.f))
	float TraceDistanceUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagons", meta = (DisplayName = "Stick to ground"))
	bool bStickToGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagons", meta = (UIMin = -10000.f, UIMax = 10000.f))
	float FlyHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagons")
	float Scale;

	UFUNCTION(BlueprintCallable, Category = "Hexagons")
	void UpdateGrid();

	UFUNCTION(BlueprintCallable, Category = "Hexagons", meta = (DisplayName = "Get Hexagon Container by type"))
	UInstancedStaticMeshComponent* GetHexagonContainerFromType(EHexagonType Type);

	UFUNCTION(BlueprintCallable, Category = "Hexagons", meta = (DisplayName = "Get Hexagon Container"))
	UInstancedStaticMeshComponent* GetHexagonContainer(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Hexagons", meta = (DisplayName = "Get number of Hexagon Containers"))
	int32 GetHexagonContainerCount();

	/*
	 Sets the hexagons and updates the grid.
	*/
	UFUNCTION(BlueprintCallable, Category = "Hexagons")
	void SetHexagons(const TArray<FHexagon>& Hexagons);

	// Sets default values for this actor's properties
	AHexagons();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UInstancedStaticMeshComponent* AddHexagonContainer(EHexagonType type, FName name, UStaticMesh* Mesh, TArray<UMaterialInterface*>& Materials);
	
	float CalculateZ(float X, float Y, float Z_start, float Z_end);

	void HexToSpace(int32 X, int32 Y, FVector& result);
};
