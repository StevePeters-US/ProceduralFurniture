// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralResizer.h"


// Sets default values
AProceduralResizer::AProceduralResizer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//XPlane
	XPlane = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("XPlane"));
	XPlane->SetupAttachment(RootComponent);
	//YPlane
	YPlane = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("YPlane"));
	YPlane->SetupAttachment(RootComponent);
	//ZPlane
	ZPlane = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ZPlane"));
	ZPlane->SetupAttachment(RootComponent);

	ResizerMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMesh>(this, TEXT("ResizerMesh"));
	//ResizerMesh->AddToRoot();
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObj(TEXT("StaticMesh'/Game/Pro_Furniture/Meshes/Countertops/Counter_Base.Counter_Base'"));
	ResizerMesh = CubeMeshObj.Object;

	ResizedMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ResizedMesh"));
	ResizedMesh->SetupAttachment(RootComponent);
	ResizedMesh->SetStaticMesh(CubeMeshObj.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("Plane'/Engine/BasicShapes/Plane.Plane'"));
	if (MeshObj.Succeeded())
	{
		XPlane->SetStaticMesh(MeshObj.Object);

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>  XMeshMat(TEXT("MaterialInstanceConstant'/Game/Pro_Furniture/Materials/Utility/ResizerPlane_X.ResizerPlane_X'"));
		if (XMeshMat.Succeeded())
			XPlane->SetMaterial(0, XMeshMat.Object);

		XPlane->SetSimulatePhysics(false);
		XPlane->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		XPlane->SetNotifyRigidBodyCollision(false);
		XPlane->SetHiddenInGame(true);

		XPlane->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));



		YPlane->SetStaticMesh(MeshObj.Object);
		
		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>  YMeshMat(TEXT("MaterialInstanceConstant'/Game/Pro_Furniture/Materials/Utility/ResizerPlane_Y.ResizerPlane_Y'"));
		if (YMeshMat.Succeeded())
			YPlane->SetMaterial(0, YMeshMat.Object);

		YPlane->SetSimulatePhysics(false);
		YPlane->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		YPlane->SetNotifyRigidBodyCollision(false);
		YPlane->SetHiddenInGame(true);

		YPlane->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));



		ZPlane->SetStaticMesh(MeshObj.Object);

		static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>  ZMeshMat(TEXT("MaterialInstanceConstant'/Game/Pro_Furniture/Materials/Utility/ResizerPlane_Z.ResizerPlane_Z'"));
		if (ZMeshMat.Succeeded())
			ZPlane->SetMaterial(0, ZMeshMat.Object);

		ZPlane->SetSimulatePhysics(false);
		ZPlane->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ZPlane->SetNotifyRigidBodyCollision(false);
		ZPlane->SetHiddenInGame(true);

		//ZPlane->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	}
	

	
}

// Called when the game starts or when spawned
void AProceduralResizer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProceduralResizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralResizer::OnConstruction(const FTransform & Transform)
{
	XPlane->SetVisibility(XPlane_Visible);
	XPlane->SetRelativeLocation(FVector(XPlane_Offset, 0.0f, 0.0f));

	YPlane->SetVisibility(YPlane_Visible);
	YPlane->SetRelativeLocation(FVector(0.0f, YPlane_Offset, 0.0f));

	ZPlane->SetVisibility(ZPlane_Visible);
	ZPlane->SetRelativeLocation(FVector(0.0f, 0.0f, ZPlane_Offset));

	if (ResizerMesh != nullptr)
	{
		FString MeshPath = ResizerMesh->GetPathName();

		//GLog->Log(MeshPath);
		//Or convert Pathname fstring to a tchar* (which the TEXT macro does to manually entered text)
		//const TCHAR* t = *MeshPath;

		//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj( *MeshPath);
		
		//if (MeshObj.Succeeded())
		//{
			ResizedMesh->SetStaticMesh( LoadObjFromPath<UStaticMesh>(*MeshPath));
		//}
			//MeshComponent->section

			int numSections =  MeshComponent->GetNumSections();
			GLog->Log(FString::FromInt(numSections));

			//MeshComponent->BeginMeshSectionUpdate();
	}
}

