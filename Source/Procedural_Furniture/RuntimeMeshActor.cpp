// Fill out your copyright notice in the Description page of Project Settings.

#include "RuntimeMeshActor.h"


// https://answers.unrealengine.com/questions/142283/upgrading-old-code-to-not-use-fpostconstructinitia.html
ARuntimeMeshActor::ARuntimeMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Engine/VREditor/BasicMeshes/M_Floor_01.M_Floor_01"));
	if (FoundMaterial.Succeeded())
	{
		Material = FoundMaterial.Object;
	}
	DynamicMaterialInst = UMaterialInstanceDynamic::Create(Material, NULL);

	MeshComponent = ObjectInitializer.CreateDefaultSubobject<URuntimeMeshComponent>(this, TEXT("RuntimeMesh"));
	MeshComponent->bShouldSerializeMeshData = false;
	MeshComponent->SetupAttachment(RootComponent);

}

/*
//Call to overriden onconstruction function so that the runtime mesh is rebuilt when modifying in the editor
//http://orfeasel.com/construction-script-based-on-c/
void ARuntimeMeshActor::OnConstruction(const FTransform & Transform)
{
	GLog->Log("Construction");
	if (autoGenerate)
	{
		//GenerateBeveledCube();
	}
}
*/

// Called when the game starts or when spawned
void ARuntimeMeshActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ARuntimeMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARuntimeMeshActor::GenerateMesh()
{
}

void ARuntimeMeshActor::GenerateCubeBasic()
{
	GenerateCube(FVector(10.0f, 10.0f, 10.0f), FVector(0.0f, 0.0f, 0.0f), false, DynamicMaterialInst, FLinearColor::Black, EUnitsType::Pro_AmericanStandard, 10.0f);
}

void ARuntimeMeshActor::GenerateCube(UPARAM() FVector size, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor, EUnitsType eType, float UVScale)
{
	SetScale(eType);

	MeshComponent->ClearAllMeshSections();
	FVector sizeMod = size * sMod;
	float UVX = size.X * UVScale;
	float UVY = size.Y * UVScale;
	float UVZ = size.Z * UVScale;

	Vertices.SetNum(8);
	Vertices[0].Position = FVector(0.0f, 0.0f, 0.0f);
	Vertices[1].Position = FVector(sizeMod.X, 0.0f, 0.0f);
	Vertices[2].Position = FVector(0.0f, sizeMod.Y, 0.0f);
	Vertices[3].Position = FVector(sizeMod.X, sizeMod.Y, 0.0f);

	Vertices[4].Position = FVector(0.0f, 0.0f, sizeMod.Z);
	Vertices[5].Position = FVector(sizeMod.X, 0.0f, sizeMod.Z);
	Vertices[6].Position = FVector(0.0f, sizeMod.Y, sizeMod.Z);
	Vertices[7].Position = FVector(sizeMod.X, sizeMod.Y, sizeMod.Z);

	Vertices[0].UV0 = FVector2D(UVX, 0.0f);
	Vertices[1].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[2].UV0 = FVector2D(UVX, UVY);
	Vertices[3].UV0 = FVector2D(0.0f, UVY);

	Vertices[4].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[5].UV0 = FVector2D(UVX, 0.0f);
	Vertices[6].UV0 = FVector2D(0.0f, UVY);
	Vertices[7].UV0 = FVector2D(UVX, UVY);

	CalculateOffset(Vertices, offset);

	Triangles.SetNum(12);
	//Bottom
	Triangles[0] = 0;
	Triangles[1] = 1;
	Triangles[2] = 2;

	Triangles[3] = 2;
	Triangles[4] = 1;
	Triangles[5] = 3;
	//Top
	Triangles[6] = 6;
	Triangles[7] = 5;
	Triangles[8] = 4;

	Triangles[9] = 7;
	Triangles[10] = 5;
	Triangles[11] = 6;

	GenerateMeshSection(0, vColor, Vertices, Triangles);

	Vertices[0].UV0 = FVector2D(0.0f, UVZ);
	Vertices[1].UV0 = FVector2D(UVY, UVZ);
	Vertices[2].UV0 = FVector2D(UVY, UVZ);
	Vertices[3].UV0 = FVector2D(0.0f, UVZ);

	Vertices[4].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[5].UV0 = FVector2D(UVY, 0.0f);
	Vertices[6].UV0 = FVector2D(UVY, 0.0f);
	Vertices[7].UV0 = FVector2D(0.0f, 0.0f);

	//Left
	Triangles[0] = 6;
	Triangles[1] = 0;
	Triangles[2] = 2;

	Triangles[3] = 4;
	Triangles[4] = 0;
	Triangles[5] = 6;
	//Right
	Triangles[6] = 5;
	Triangles[7] = 3;
	Triangles[8] = 1;

	Triangles[9] = 7;
	Triangles[10] = 3;
	Triangles[11] = 5;

	GenerateMeshSection(1, vColor, Vertices, Triangles);
	
	Vertices[0].UV0 = FVector2D(UVX, UVZ);
	Vertices[1].UV0 = FVector2D(0.0f, UVZ);
	Vertices[2].UV0 = FVector2D(0.0f, UVZ);
	Vertices[3].UV0 = FVector2D(UVX, UVZ);

	Vertices[4].UV0 = FVector2D(UVX, 0.0f);
	Vertices[5].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[6].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[7].UV0 = FVector2D(UVX, 0.0f);

	//Back
	Triangles[0] = 4;
	Triangles[1] = 1;
	Triangles[2] = 0;

	Triangles[3] = 5;
	Triangles[4] = 1;
	Triangles[5] = 4;
	//Front
	Triangles[6] = 2;
	Triangles[7] = 3;
	Triangles[8] = 6;

	Triangles[9] = 6;
	Triangles[10] = 3;
	Triangles[11] = 7;

	GenerateMeshSection(2, vColor, Vertices, Triangles);
		
}

void ARuntimeMeshActor::GenerateBeveledCube(FVector size, FVector offset, float bevelSize, bool createCollision, UMaterialInstance* mat, FLinearColor vertexColor, EUnitsType eType, float UVScale)
{
	GLog->Log("Generate Cube - Runtimemesh actor cpp");

	SetScale(eType);

	MeshComponent->ClearAllMeshSections();
	FVector sizeMod = size * sMod;
	float b = bevelSize * sMod;


	Vertices.SetNum(12);
	Vertices[0].Position = FVector(0.0f, 0.0f, 0.0f);
	Vertices[1].Position = FVector(sizeMod.X, 0.0f, 0.0f);
	Vertices[2].Position = FVector(0.0f, sizeMod.Y - b, 0.0f);
	Vertices[3].Position = FVector(sizeMod.X, sizeMod.Y - b, 0.0f);

	Vertices[4].Position = FVector(0.0f, 0.0f, sizeMod.Z);
	Vertices[5].Position = FVector(sizeMod.X, 0.0f, sizeMod.Z);
	Vertices[6].Position = FVector(0.0f, sizeMod.Y - b, sizeMod.Z);
	Vertices[7].Position = FVector(sizeMod.X, sizeMod.Y - b, sizeMod.Z);

	Vertices[8].Position = FVector(b, sizeMod.Y, b);
	Vertices[9].Position = FVector(sizeMod.X - b, sizeMod.Y, b);
	Vertices[10].Position = FVector(b, sizeMod.Y, sizeMod.Z - b);
	Vertices[11].Position = FVector(sizeMod.X - b, sizeMod.Y, sizeMod.Z - b);

	Vertices[0].UV0 = FVector2D(0.0f, 1.0f);
	Vertices[1].UV0 = FVector2D(1.0f, 1.0f);
	Vertices[2].UV0 = FVector2D(1.0f, 0.0f);
	Vertices[3].UV0 = FVector2D(0.0f, 0.0f);

	Vertices[4].UV0 = FVector2D(0.0f, 1.0f);
	Vertices[5].UV0 = FVector2D(1.0f, 1.0f);
	Vertices[6].UV0 = FVector2D(1.0f, 0.0f);
	Vertices[7].UV0 = FVector2D(0.0f, 0.0f);

	Vertices[8].UV0 = FVector2D(0.0f, 1.0f);
	Vertices[9].UV0 = FVector2D(1.0f, 1.0f);
	Vertices[10].UV0 = FVector2D(1.0f, 0.0f);
	Vertices[11].UV0 = FVector2D(0.0f, 0.0f);

	CalculateOffset(Vertices, offset);

	Triangles.SetNum(12);
	Triangles[0] = 0;
	Triangles[1] = 1;
	Triangles[2] = 2;

	Triangles[3] = 2;
	Triangles[4] = 1;
	Triangles[5] = 3;

	Triangles[6] = 6;
	Triangles[7] = 5;
	Triangles[8] = 4;

	Triangles[9] = 7;
	Triangles[10] = 5;
	Triangles[11] = 6;

	//Top - Bottom
	GenerateMeshSection(0, vColor, Vertices, Triangles);

	Triangles[0] = 6;
	Triangles[1] = 0;
	Triangles[2] = 2;

	Triangles[3] = 4;
	Triangles[4] = 0;
	Triangles[5] = 6;

	Triangles[6] = 5;
	Triangles[7] = 3;
	Triangles[8] = 1;

	Triangles[9] = 7;
	Triangles[10] = 3;
	Triangles[11] = 5;

	//Left - Right
	GenerateMeshSection(1, vColor, Vertices, Triangles);

	Triangles[0] = 4;
	Triangles[1] = 1;
	Triangles[2] = 0;

	Triangles[3] = 5;
	Triangles[4] = 1;
	Triangles[5] = 4;

	Triangles[6] = 8;
	Triangles[7] = 9;
	Triangles[8] = 10;

	Triangles[9] = 10;
	Triangles[10] = 9;
	Triangles[11] = 11;

	//Back - Front
	GenerateMeshSection(2, vColor, Vertices, Triangles);

	Triangles[0] = 8;
	Triangles[1] = 6;
	Triangles[2] = 2;

	Triangles[3] = 8;
	Triangles[4] = 10;
	Triangles[5] = 6;

	Triangles[6] = 9;
	Triangles[7] = 2;
	Triangles[8] = 3;

	Triangles[9] = 9;
	Triangles[10] = 8;
	Triangles[11] = 2;

	//Back - Front
	GenerateMeshSection(3, vColor, Vertices, Triangles);

	Triangles[0] = 7;
	Triangles[1] = 11;
	Triangles[2] = 3;

	Triangles[3] = 11;
	Triangles[4] = 9;
	Triangles[5] = 3;

	Triangles[6] = 7;
	Triangles[7] = 10;
	Triangles[8] = 11;

	Triangles[9] = 7;
	Triangles[10] = 6;
	Triangles[11] = 10;

	//Back - Front
	GenerateMeshSection(4, vColor, Vertices, Triangles);
}

void ARuntimeMeshActor::GenerateMeshSection(int sectionID, FColor vertexColor, TArray<FRuntimeMeshVertexSimple>& InVertices, TArray<int32>& InTriangles)
{
	//FBox BoundingBox = FBox(-Size / 2.0f, Size / 2.0f);
	
	
	//MeshComponent->CreateMeshSection(sectionID, Vertices, Triangles, BoundingBox, false, EUpdateFrequency::Infrequent);
	URuntimeMeshLibrary::CalculateTangentsForMesh(InVertices, InTriangles);
	MeshComponent->CreateMeshSection(sectionID, Vertices, Triangles, false, EUpdateFrequency::Infrequent);
}

void ARuntimeMeshActor::ProjectUVsXAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale)
{
	for (int i = 0; i < InVertices.Num(); i++)
	{
		InVertices[i].UV0 = FVector2D(InVertices[i].Position.Y * UVScale, InVertices[i].Position.Z * UVScale);
	}
}

void ARuntimeMeshActor::ProjectUVsYAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale)
{
	for (int i = 0; i < InVertices.Num(); i++)
	{
		InVertices[i].UV0 = FVector2D(InVertices[i].Position.X * UVScale, InVertices[i].Position.Z * UVScale);
	}
}

void ARuntimeMeshActor::ProjectUVsZAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale)
{
	for (int i = 0; i < InVertices.Num(); i++)
	{
		InVertices[i].UV0 = FVector2D(InVertices[i].Position.X * UVScale, InVertices[i].Position.Y * UVScale);
	}
}

void ARuntimeMeshActor::ProjectUVsXYAxis(FRuntimeMeshVertexSimple& InVertex, bool worldSpace, float UVScale, float angle)
{
	angle = angle * (PI / 180);

	InVertex.UV0 = FVector2D(((InVertex.Position.X * (FMath::Cos(angle))) - (InVertex.Position.Y * (FMath::Sin(angle)))) * UVScale,
		 InVertex.Position.Z * UVScale);
}

//	From: http://stackoverflow.com/questions/620745/c-rotating-a-vector-around-a-certain-point
//x = ((x - x_origin) * cos(angle)) - ((y_origin - y) * sin(angle)) + x_origin
//y = ((y_origin - y) * cos(angle)) - ((x - x_origin) * sin(angle)) + y_origin
FVector ARuntimeMeshActor::RotateVertexAboutPoint(FVector vertexPos, FVector rotationPointPos, float angle)
{
	float tempAngle = (FMath::GetMappedRangeValue(FVector2D(0.0f, 360.0f), FVector2D(360.0f, 0.0f), angle) - 90.0f) * PI / 180;
	FVector outVector( ((- FMath::Cos(tempAngle) * (vertexPos.X - rotationPointPos.X)) - ((FMath::Sin(tempAngle) * (rotationPointPos.Y - vertexPos.Y))) + rotationPointPos.X),
		(((rotationPointPos.Y - vertexPos.Y) * FMath::Cos(tempAngle)) - ((vertexPos.X - rotationPointPos.X) * FMath::Sin(tempAngle)) + rotationPointPos.Y),
		vertexPos.Z);

	return outVector;
}

void ARuntimeMeshActor::CalculateOffset(TArray<FRuntimeMeshVertexSimple>& Vertices, FVector offset)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		Vertices[i].Position.X += (offset.X* sMod);
		Vertices[i].Position.Y += (offset.Y* sMod);
		Vertices[i].Position.Z += (offset.Z* sMod);
	}
}

void ARuntimeMeshActor::SetScale(EUnitsType eType)
{
	if (eType == EUnitsType::Pro_AmericanStandard)
	{
		sMod = 2.54f;
	}
}
