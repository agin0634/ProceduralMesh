// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TerrainMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Terrain"));

}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	
	CreateQuads();
	
	TArray<FLinearColor> vertexColors;

	TArray<FProcMeshTangent> tangents;

	TerrainMesh->CreateMeshSection_LinearColor(0, Vertexes, Triangles, Normals, UV0, vertexColors, tangents, true);
	if (TerrainMaterial != nullptr) 
	{
		TerrainMesh->SetMaterial(0, TerrainMaterial);
	}
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrain::CreateQuads()
{
	int32 HorizontalIndex;
	int32 VerticalIndex;
	TArray<FVector> Vertexes_tmp;
	TArray<int32> Triangles_tmp;

	for (int32 i = 0; i < Length; i++)
	{
		HorizontalIndex = i;
		for (int32 j = 0; j < Width; j++)
		{
			VerticalIndex = j;
			// Generate Vertexes
			float z = FMath::RandRange(MinHeight, MaxHeight);
			Vertexes_tmp.Add(FVector(HorizontalIndex * TileLengthX, VerticalIndex * TileLengthY, z));

			// Generate Triangles
			if (HorizontalIndex != Length - 1 && VerticalIndex != Width - 1)
			{
				int32 x = HorizontalIndex * Width + VerticalIndex;
				
				UKismetProceduralMeshLibrary::ConvertQuadToTriangles(Triangles_tmp, x, x + 1, x + Width + 1, x + Width);
			}

			// Generate UV0
			UV0.Add(FVector2D((1 / Length - 1) * HorizontalIndex * UVScale.X, (1 / Width - 1) * VerticalIndex * UVScale.Y));

		}

	}

	// Generate Normals
	int32 TrianglesCounts = (Length - 1) * (Width - 1) * 2;
	int32 CurrentVertexIndex = 0;

	for (int32 i = 0; i < TrianglesCounts; i++)
	{
		FVector a = Vertexes_tmp[Triangles_tmp[CurrentVertexIndex]];
		FVector b = Vertexes_tmp[Triangles_tmp[CurrentVertexIndex + 1]];
		FVector c = Vertexes_tmp[Triangles_tmp[CurrentVertexIndex + 2]];

		FVector normal = FVector::CrossProduct(c - a, b - a).GetSafeNormal();

		Normals.Add(normal);
		Normals.Add(normal);
		Normals.Add(normal);
		CurrentVertexIndex += 3;
	}

	Vertexes = Vertexes_tmp;
	Triangles = Triangles_tmp;
}