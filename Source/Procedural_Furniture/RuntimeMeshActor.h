// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "ProMesh_Data.h"
#include "RuntimeMeshActor.generated.h"

UCLASS()
class PROCEDURAL_FURNITURE_API ARuntimeMeshActor : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ARuntimeMeshActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = Components)
		USceneComponent* Root;

	//Scale modifier (1.0 for metric, 2.54 for Imperial)
	float sMod = 1.0f;

	//Material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
		UMaterialInterface* MaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
		UMaterial* Material;
	UMaterialInstanceDynamic* DynamicMaterialInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool autoGenerate = false;

	UFUNCTION(BlueprintCallable, Category = "Default")
		void GenerateMesh();

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCubeBasic();

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCube(UPARAM() FVector size, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor, EUnitsType eType, float UVScale);

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateBeveledCube(FVector size, FVector offset, float bevelSize, bool createCollision,UMaterialInstance* mat, FLinearColor vertexColor, EUnitsType eType, float UVScale);

	//UFUNCTION(BlueprintCallable, Category = "Mesh")
	void ProjectUVsXAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale);
	
	void ProjectUVsYAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale);

	void ProjectUVsZAxis(TArray<FRuntimeMeshVertexSimple>& InVertices, bool worldSpace, float UVScale);

	void ProjectUVsXYAxis(FRuntimeMeshVertexSimple& InVertex, bool worldSpace, float UVScale, float angle);

		void GenerateMeshSection(int sectionID, FColor vertexColor, TArray<FRuntimeMeshVertexSimple>& InVertices, TArray<int32>& InTriangles);
		void SetScale(EUnitsType EType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		USceneComponent* RootNode;

	UPROPERTY()
		URuntimeMeshComponent* MeshComponent;

	void CalculateOffset(TArray<FRuntimeMeshVertexSimple>& InVertices, FVector offset);

	FVector RotateVertexAboutPoint(FVector vertexPos, FVector rotationPointPos, float angle);

	FColor vColor;
	TArray<int32> Triangles;
	TArray<FRuntimeMeshVertexSimple> Vertices;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual void OnConstruction(const FTransform& Transform) override;
	
private:





	//From https://github.com/SiggiG/ProceduralMeshes/blob/master/Source/ProceduralMeshes/Private/SimpleCubeActor.cpp
	void GenerateCube_SG(TArray<FRuntimeMeshVertexSimple>& InVertices, TArray<int32>& InTriangles, FVector InSize);
	void BuildQuad(TArray<FRuntimeMeshVertexSimple>& InVertices, TArray<int32>& InTriangles, FVector BottomLeft, FVector BottomRight, FVector TopRight, FVector TopLeft, int32& VertexOffset, int32& TriangleOffset, FPackedNormal Normal, FPackedNormal Tangent);

	// Mesh buffers
	void SetupMeshBuffers();
	bool bHaveBuffersBeenInitialized = false;


};
