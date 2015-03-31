// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Hexagon.generated.h"

class AHexGrid;

UENUM()
enum class EHexagonType : uint8 {
	HE_Default UMETA(DisplayName = "Default")
	// Add more later on
};

UCLASS()
class UHexagon : public UObject {
	GENERATED_BODY()

	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hexagon")
		EHexagonType HexagonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
		FTransform HexagonTransform;

	UPROPERTY()
		AHexGrid* Owner;

public:
	/*
	UHexagon(AHexGrid* Owner, EHexagonType Type, FTransform Location);

	~UHexagon();

	FTransform GetTransform();

	void SetTransform(FTransform& Transform);

	EHexagonType GetHexagonType();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;
#endif

protected:

	void UpdateHexagon();

	void RemoveHexagon();

	void CreateHexagon();
	*/
private:

	int32 ArrayIndex;

};
