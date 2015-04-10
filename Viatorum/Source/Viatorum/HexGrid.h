// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Landscape.h"
#include "HexGrid.generated.h"


UENUM(BlueprintType)
enum class EHexagonType : uint8 {
	HE_Default UMETA(DisplayName = "Default"),
	HE_Algae UMETA(DisplayName = "Algae overgrown")

};

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

	AHexGrid();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

#if WITH_EDITOR

	virtual void PostEditMove(bool bFinished) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;

#endif

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	void UpdateGrid();

	UFUNCTION(BlueprintCallable, Category = "Hexagon Grid")
	UInstancedStaticMeshComponent* GetHexagonContainer(EHexagonType Type);

private:

	template<typename T>
	FORCEINLINE T* FindObject(FName name);

	UMaterialInstance* MakeDynamicInstance(UMaterial* Material);

	UInstancedStaticMeshComponent* AddHexagonContainer(EHexagonType type, FName name, UStaticMesh* Mesh, TArray<UMaterialInterface*>& Materials);

	float CalculateZ(float X, float Y, float Z_start, float Z_end);

	TMap<uint8, UInstancedStaticMeshComponent*> HexagonContainers;
};
