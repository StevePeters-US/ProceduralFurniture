// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuntimeMeshActor.h"
#include "Cab_Parts_RT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROCEDURAL_FURNITURE_API ACab_Parts_RT : public ARuntimeMeshActor
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCabinetSide(UPARAM() FVector size, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
			float TKHeight, float TKDepth, float depthOffsetL, float depthOffsetR, EUnitsType eType, float UVScale);
	
	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCornerCabinetBottomStraight(float depth1, float depth2, float width1, float width2, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
			float angle, float cabinetPanelThickness, EUnitsType eType, float UVScale);

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCornerCabinetBottomAngled(float depth1, float depth2, float width1, float width2, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
			float angle, float cabinetPanelThickness, EUnitsType eType, float UVScale);

	UFUNCTION(BlueprintCallable, Category = "Parts")
		void GenerateCornerCabinetCornerBack(FVector size, float angle, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat,
			UPARAM() FLinearColor vertexColor, EUnitsType eType, bool LEdgeOffset, bool REdgeOffset, float UVScale);

	float CalcCornerAngleDoorCenterVertexPos(float angle, float cabinetWidth, float CabinetDepth_2);

private:

	float CalcBackEdgeOffset(float cabinetPanelThickness, float cabinetAngle);
};
