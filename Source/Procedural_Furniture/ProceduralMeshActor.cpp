// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMeshActor.h"

// https://answers.unrealengine.com/questions/142283/upgrading-old-code-to-not-use-fpostconstructinitia.html
AProceduralMeshActor::AProceduralMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	RootComponent = Root;
	/*
	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Engine/VREditor/BasicMeshes/M_Floor_01.M_Floor_01"));
	if (FoundMaterial.Succeeded())
	{
		Material = FoundMaterial.Object;
	}
	DynamicMaterialInst = UMaterialInstanceDynamic::Create(Material, NULL);

	MeshComponent = ObjectInitializer.CreateDefaultSubobject<URuntimeMeshComponent>(this, TEXT("RuntimeMesh"));
	MeshComponent->bShouldSerializeMeshData = false;
	MeshComponent->SetupAttachment(RootComponent);
	*/
}



// Called when the game starts or when spawned
void AProceduralMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
