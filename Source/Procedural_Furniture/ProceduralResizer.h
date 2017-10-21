// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshActor.h"
#include "ProceduralResizer.generated.h"

UCLASS(Blueprintable)
class PROCEDURAL_FURNITURE_API AProceduralResizer : public ARuntimeMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralResizer(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* ResizerMesh;

		UStaticMeshComponent* ResizedMesh;

	//UPROPERTY(VisibleAnywhere, Category = "ResizePlanes")
		UStaticMeshComponent* XPlane;

	//UPROPERTY(VisibleAnywhere, Category = "ResizePlanes")
		UStaticMeshComponent* YPlane;

	//UPROPERTY(VisibleAnywhere, Category = "ResizePlanes")
		UStaticMeshComponent* ZPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		bool XPlane_Visible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		bool YPlane_Visible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		bool ZPlane_Visible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		float XPlane_Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		float YPlane_Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ResizePlanes")
		float ZPlane_Offset;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//https://wiki.unrealengine.com/Dynamic_Load_Object

	//Get Path
	static FORCEINLINE FName GetObjPath(const UObject* Obj)
	{
		if (!Obj)
		{
			return NAME_None;
		}
		//~

		FStringAssetReference ThePath = FStringAssetReference(Obj);

		if (!ThePath.IsValid()) return NAME_None;

		//The Class FString Name For This Object
		FString Str = Obj->GetClass()->GetDescription();

		Str += "'";
		Str += ThePath.ToString();
		Str += "'";

		return FName(*Str);
	}

	//TEMPLATE Load Obj From Path
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	// Load PS From Path 
	static FORCEINLINE UParticleSystem* LoadPSFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return LoadObjFromPath<UParticleSystem>(Path);
	}


	// Load Material From Path 
	static FORCEINLINE UMaterialInterface* LoadMatFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return LoadObjFromPath<UMaterialInterface>(Path);
	}

	// Load Static Mesh From Path 
	static FORCEINLINE UStaticMesh* LoadMeshFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return LoadObjFromPath<UStaticMesh>(Path);
	}
	
	
};
