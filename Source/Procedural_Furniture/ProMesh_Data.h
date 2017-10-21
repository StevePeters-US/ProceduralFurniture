// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProMesh_Data.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EUnitsType : uint8
{
	Pro_AmericanStandard 	UMETA(DisplayName = "IN"),
	Pro_Metric 				UMETA(DisplayName = "CM")
};

UENUM(BlueprintType)
enum class ECabinetType : uint8
{
	Base					UMETA(DisplayName = "Base"),
	BaseCorner_Straight 	UMETA(DisplayName = "Base Corner Straight"),
	BaseCorner_Angled		UMETA(DisplayName = "Base Corner Angled"),
	Wall 					UMETA(DisplayName = "Wall"),
	WallCorner_Straight 	UMETA(DisplayName = "Wall Corner Straight"),
	WallCorner_Angled		UMETA(DisplayName = "Wall Corner Angled")
};


UCLASS()
class PROCEDURAL_FURNITURE_API AProMesh_Data : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProMesh_Data();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
