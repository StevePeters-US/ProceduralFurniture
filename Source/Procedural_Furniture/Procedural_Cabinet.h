// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cab_Parts_RT.h"
#include "ProMesh_Data.h"
#include "Procedural_Cabinet.generated.h"

UCLASS(Blueprintable)
class PROCEDURAL_FURNITURE_API AProcedural_Cabinet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedural_Cabinet(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = Components)
		USceneComponent* Root;

	//--------------------------------
	//Functions
	//--------------------------------

	void GenerateCabinet();
	void Generate_BaseCabinet();
	void Generate_BaseCornerStraight_Cabinet();
	void Generate_BaseCornerAngled_Cabinet();
	void Generate_WallCabinet();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
		bool autoGenerate = false;

	//--------------------------------
	//Dimensions
	//--------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float CabinetHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float CabinetWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float CabinetDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float CabinetPanelThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float TKHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float TKDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float DrawerFrontHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float DoorGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
		float ScribeWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0"))
		float CabinetAngle;

	//--------------------------------
	//Properties
	//--------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		EUnitsType eType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		ECabinetType cType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.0", ClampMax = "6.0", UIMin = "0.0", UIMax = "6.0"))
		float FinishLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.0", ClampMax = "6.0", UIMin = "0.0", UIMax = "6.0"))
		float FinishRight;

	//Scale modifier (1.0 for metric, 2.54 for Imperial)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		float sMod = 2.54f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		bool bCreateCollision = false;

	//--------------------------------
	//Rendering
	//--------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
		UMaterial* Material;
	UMaterialInstanceDynamic* DynamicMaterialInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
		float UVScale;

	//https://answers.unrealengine.com/questions/221783/add-child-actor-component-in-c.html
	UPROPERTY(VisibleAnywhere, Category = "Parts")
		ACab_Parts_RT* CabinetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		USceneComponent* RootNode;

	UPROPERTY(EditDefaultsOnly, Category = "Parts")
		TSubclassOf<ACab_Parts_RT> partOne = ACab_Parts_RT::StaticClass();

	UPROPERTY(EditDefaultsOnly, Category = "Parts")
		TSubclassOf<ACab_Parts_RT> part = ACab_Parts_RT::StaticClass();

	TArray<ACab_Parts_RT> parts;

	void DestroyChildren();

	//--------------------------------
	//Door blueprint
	//--------------------------------
	//https://answers.unrealengine.com/questions/53689/spawn-blueprint-from-c.html
	TSubclassOf<class AProcedural_Cabinet> Procedural_Cabinet_Door;
	
	void SpawnDoor();

	//--------------------------------
	//Functions
	//--------------------------------
	FVector GetCornerRightPanelOffset();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginDestroy();
};
