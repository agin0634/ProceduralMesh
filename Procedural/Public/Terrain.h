// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Materials/Material.h"
#include "Terrain.generated.h"

UCLASS()
class PROCEDURAL_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	UProceduralMeshComponent* TerrainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Length = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Width = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHeight = -50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeight = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TileLengthX = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TileLengthY = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* TerrainMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D UVScale = FVector2D(1, 1);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	TArray<FVector> Vertexes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Normals;

	TArray<int32> Triangles;
	TArray<FVector2D> UV0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateQuads();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
