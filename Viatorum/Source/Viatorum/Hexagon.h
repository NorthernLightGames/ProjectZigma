// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Hexagon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIATORUM_API UHexagon : public USceneComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	// Sets default values for this component's properties
	UHexagon();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
