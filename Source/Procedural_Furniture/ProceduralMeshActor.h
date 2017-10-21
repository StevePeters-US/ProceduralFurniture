// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProMesh_Data.h"
#include "ProceduralMeshActor.generated.h"


struct ProceduralMeshVertex
{
	FVector position;
	FVector2D UV;
};

UCLASS()
class PROCEDURAL_FURNITURE_API AProceduralMeshActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AProceduralMeshActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = Components)
		USceneComponent* Root;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	/*
	UFUNCTION(BlueprintCallable, Category = "Default")
		void GenerateMesh();

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCubeBasic();

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCube(UPARAM() FVector size, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor, EUnitsType eType, float UVScale);

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateBeveledCube(FVector size, FVector offset, float bevelSize, bool createCollision, UMaterialInstance* mat, FLinearColor vertexColor, EUnitsType eType, float UVScale);


	void ProjectUVsYAxis(TArray<ProceduralMeshVertex>& InVertices, bool worldSpace, float UVScale);

	void ProjectUVsZAxis(TArray<ProceduralMeshVertex>& InVertices, bool worldSpace, float UVScale);

	void ProjectUVsXYAxis(ProceduralMeshVertex& InVertex, bool worldSpace, float UVScale, float angle);

	void GenerateMeshSection(int sectionID, FColor vertexColor, TArray<ProceduralMeshVertex>& InVertices, TArray<int32>& InTriangles);
	void SetScale(EUnitsType EType);
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		USceneComponent* RootNode;

	UPROPERTY()
		UProceduralMeshComponent* MeshComponent;

	void CalculateOffset(TArray<ProceduralMeshVertex>& InVertices, FVector offset);

	FVector RotateVertexAboutPoint(FVector vertexPos, FVector rotationPointPos, float angle);

	FColor vColor;
	TArray<int32> Triangles;
	TArray<ProceduralMeshVertex> Vertices;
	
};
