// Fill out your copyright notice in the Description page of Project Settings.

#include "Cab_Parts_RT.h"

void ACab_Parts_RT::GenerateCabinetSide(UPARAM() FVector size, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
	float TKHeight, float TKDepth, float depthOffsetL, float depthOffsetR, EUnitsType eType, float UVScale)
{
	SetScale(eType);

	MeshComponent->ClearAllMeshSections();

	float UVX = size.X * UVScale;
	float UVY = size.Y * UVScale;
	float UVZ = size.Z * UVScale;
	float TKD = TKDepth * UVScale;
	float TKH = TKHeight * UVScale;

	depthOffsetL *= sMod;
	depthOffsetR *= sMod;
	TKDepth *= sMod;
	TKHeight *= sMod;
	FVector sizeMod = size * sMod;
	
	Vertices.SetNum(12);
	Vertices[0].Position = FVector(0.0f, sizeMod.Y - TKDepth + depthOffsetL, 0.0f);
	Vertices[1].Position = FVector(sizeMod.X, sizeMod.Y - TKDepth + depthOffsetR, 0.0f);
	Vertices[2].Position = FVector(0.0f, 0.0f, 0.0f);
	Vertices[3].Position = FVector(sizeMod.X, 0.0f, 0.0f);

	Vertices[4].Position = FVector(0.0f, sizeMod.Y + depthOffsetL, TKHeight);
	Vertices[5].Position = FVector(sizeMod.X, sizeMod.Y + depthOffsetR, TKHeight);
	Vertices[6].Position = FVector(0.0f, sizeMod.Y - TKDepth + depthOffsetL, TKHeight);
	Vertices[7].Position = FVector(sizeMod.X, sizeMod.Y - TKDepth + depthOffsetR, TKHeight);

	Vertices[8].Position = FVector(0.0f, sizeMod.Y + depthOffsetL, sizeMod.Z);
	Vertices[9].Position = FVector(sizeMod.X, sizeMod.Y + depthOffsetR, sizeMod.Z);
	Vertices[10].Position = FVector(0.0f, 0.0f, sizeMod.Z);
	Vertices[11].Position = FVector(sizeMod.X, 0.0f, sizeMod.Z);

	CalculateOffset(Vertices, offset);

	ProjectUVsZAxis(Vertices, false, UVScale);

	//Bottom - Top
	Triangles.SetNum(18);

	Triangles[0] = 2;
	Triangles[1] = 1;
	Triangles[2] = 0;

	Triangles[3] = 3;
	Triangles[4] = 1;
	Triangles[5] = 2;

	Triangles[6] = 4;
	Triangles[7] = 6;
	Triangles[8] = 5;

	Triangles[9] = 5;
	Triangles[10] = 6;
	Triangles[11] = 7;

	Triangles[12] = 8;
	Triangles[13] = 9;
	Triangles[14] = 10;

	Triangles[15] = 10;
	Triangles[16] = 9;
	Triangles[17] = 11;

	GenerateMeshSection(0, vColor, Vertices, Triangles);

	ProjectUVsXAxis(Vertices, false, UVScale);

	//Left -  Right
	Triangles.SetNum(24);

	Triangles[0] = 2;
	Triangles[1] = 0;
	Triangles[2] = 6;

	Triangles[3] = 6;
	Triangles[4] = 10;
	Triangles[5] = 2;

	Triangles[6] = 10;
	Triangles[7] = 6;
	Triangles[8] = 8;

	Triangles[9] = 6;
	Triangles[10] = 4;
	Triangles[11] = 8;

	Triangles[12] = 1;
	Triangles[13] = 3;
	Triangles[14] = 7;

	Triangles[15] = 7;
	Triangles[16] = 3;
	Triangles[17] = 11;

	Triangles[18] = 9;
	Triangles[19] = 7;
	Triangles[20] = 11;

	Triangles[21] = 5;
	Triangles[22] = 7;
	Triangles[23] = 9;

	GenerateMeshSection(1, vColor, Vertices, Triangles);

	ProjectUVsYAxis(Vertices, false, UVScale);

	//Back front
	Triangles.SetNum(18);
	Triangles[0] = 10;
	Triangles[1] = 3;
	Triangles[2] = 2;

	Triangles[3] = 11;
	Triangles[4] = 3;
	Triangles[5] = 10;

	Triangles[6] = 4;
	Triangles[7] = 5;
	Triangles[8] = 8;

	Triangles[9] = 8;
	Triangles[10] = 5;
	Triangles[11] = 9;

	Triangles[12] = 0;
	Triangles[13] = 1;
	Triangles[14] = 6;

	Triangles[15] = 6;
	Triangles[16] = 1;
	Triangles[17] = 7;

	GenerateMeshSection(2, vColor, Vertices, Triangles);
}

void ACab_Parts_RT::GenerateCornerCabinetBottomStraight(float depth1, float depth2, float width1, float width2, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
	float angle, float cabinetPanelThickness, EUnitsType eType, float UVScale)
{
	SetScale(eType);

	MeshComponent->ClearAllMeshSections();

	//float UVX = size.X * UVScale;
	//float UVY = size.Y * UVScale;
	//float UVZ = size.Z * UVScale;
	float D1 = depth1 * sMod;
	float D2 = depth2 * sMod;
	float W1 = width1 * sMod;
	float W2 = width2 * sMod;
	float CT = cabinetPanelThickness * sMod;

	//Inside corner vert X position
	float IC = CalcCornerAngleDoorCenterVertexPos(angle, width1, depth2) * sMod; 

	Vertices.SetNum(12);
	Vertices[0].Position = FVector(CT, 0.0f, 0.0f);
	Vertices[1].Position = FVector(W1, 0.0f, 0.0f);
	Vertices[2].Position = FVector(CT, D1, 0.0f);
	Vertices[3].Position = FVector(IC, D1, 0.0f);

	Vertices[4].Position = FVector(W1 - D2, W1 - CT, 0.0f);
	Vertices[5].Position = FVector(W1, W1 - CT, 0.0f);
	Vertices[6].Position = FVector(CT, 0.0f, CT);
	Vertices[7].Position = FVector(W1, 0.0f, CT);

	Vertices[8].Position = FVector(CT, D1, CT);
	Vertices[9].Position = FVector(IC, D1, CT);
	Vertices[10].Position = FVector(W1 - D2, W1 - CT, CT);
	Vertices[11].Position = FVector(W1, W1 - CT, CT);

	//Rotate verts based on cabinet angle
	Vertices[4].Position = RotateVertexAboutPoint(Vertices[4].Position, Vertices[1].Position, angle);
	Vertices[5].Position = RotateVertexAboutPoint(Vertices[5].Position, Vertices[1].Position, angle);
	Vertices[10].Position = RotateVertexAboutPoint(Vertices[10].Position, Vertices[1].Position, angle);
	Vertices[11].Position = RotateVertexAboutPoint(Vertices[11].Position, Vertices[1].Position, angle);

	CalculateOffset(Vertices, offset);

	ProjectUVsZAxis(Vertices, false, UVScale);

	//Bottom - Top
	Triangles.SetNum(18);

	Triangles[0] = 0;
	Triangles[1] = 1;
	Triangles[2] = 2;

	Triangles[3] = 2;
	Triangles[4] = 1;
	Triangles[5] = 4;

	Triangles[6] = 4;
	Triangles[7] = 1;
	Triangles[8] = 5;

	Triangles[9] = 8;
	Triangles[10] = 7;
	Triangles[11] = 6;

	Triangles[12] = 8;
	Triangles[13] = 10;
	Triangles[14] = 11;

	Triangles[15] = 8;
	Triangles[16] = 11;
	Triangles[17] = 7;

	GenerateMeshSection(0, vColor, Vertices, Triangles);
	/*
	Vertices[0].UV0 = FVector2D(UVY - TKD, 0.0f);
	Vertices[1].UV0 = FVector2D(UVY - TKD, 0.0f);
	Vertices[2].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[3].UV0 = FVector2D(0.0f, 0.0f);

	Vertices[4].UV0 = FVector2D(UVY, TKH);
	Vertices[5].UV0 = FVector2D(UVY, TKH);
	Vertices[6].UV0 = FVector2D(UVY - TKD, TKH);
	Vertices[7].UV0 = FVector2D(UVY - TKD, TKH);

	Vertices[8].UV0 = FVector2D(UVY, UVZ);
	Vertices[9].UV0 = FVector2D(UVY, UVZ);
	Vertices[10].UV0 = FVector2D(0.0f, UVZ);
	Vertices[11].UV0 = FVector2D(0.0f, UVZ);
	*/

	ProjectUVsXYAxis(Vertices[2], false, UVScale, FMath::GetMappedRangeValue(FVector2D(0.0f, 180.0f), FVector2D(90.0f, 180.0f), angle));
	ProjectUVsXYAxis(Vertices[4], false, UVScale, FMath::GetMappedRangeValue(FVector2D(0.0f, 180.0f), FVector2D(90.0f, 180.0f), angle));
	ProjectUVsXYAxis(Vertices[8], false, UVScale, FMath::GetMappedRangeValue(FVector2D(0.0f, 180.0f), FVector2D(90.0f, 180.0f), angle));
	ProjectUVsXYAxis(Vertices[10], false, UVScale, FMath::GetMappedRangeValue(FVector2D(0.0f, 180.0f), FVector2D(90.0f, 180.0f), angle));

	//Left -  Right
	Triangles[0] = 2;
	Triangles[1] = 4;
	Triangles[2] = 10;

	Triangles[3] = 2;
	Triangles[4] = 10;
	Triangles[5] = 8;

	Triangles[6] = 6;
	Triangles[7] = 1;
	Triangles[8] = 0;

	Triangles[9] = 7;
	Triangles[10] = 1;
	Triangles[11] = 6;

	Triangles[12] = 7;
	Triangles[13] = 5;
	Triangles[14] = 1;

	Triangles[15] = 11;
	Triangles[16] = 5;
	Triangles[17] = 7;

	GenerateMeshSection(1, vColor, Vertices, Triangles);
	
}

void ACab_Parts_RT::GenerateCornerCabinetBottomAngled(float depth1, float depth2, float width1, float width2, UPARAM() FVector offset, UPARAM() bool createCollision, UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor,
	float angle, float cabinetPanelThickness, EUnitsType eType, float UVScale)
{
	SetScale(eType);

	MeshComponent->ClearAllMeshSections();

	//float UVX = size.X * UVScale;
	//float UVY = size.Y * UVScale;
	//float UVZ = size.Z * UVScale;
	float D1 = depth1 * sMod;
	float D2 = depth2 * sMod;
	float W1 = width1 * sMod;
	float W2 = width2 * sMod;
	float CT = cabinetPanelThickness * sMod;

	//Inside corner vert X position
	float IC = CalcCornerAngleDoorCenterVertexPos(angle, width1, depth2) * sMod;

	Vertices.SetNum(12);
	Vertices[0].Position = FVector(CT, 0.0f, 0.0f);
	Vertices[1].Position = FVector(W1, 0.0f, 0.0f);
	Vertices[2].Position = FVector(CT, D1, 0.0f);
	Vertices[3].Position = FVector(IC, D1, 0.0f);

	Vertices[4].Position = FVector(W1 - D2, W1 - CT, 0.0f);
	Vertices[5].Position = FVector(W1, W1 - CT, 0.0f);
	Vertices[6].Position = FVector(CT, 0.0f, CT);
	Vertices[7].Position = FVector(W1, 0.0f, CT);

	Vertices[8].Position = FVector(CT, D1, CT);
	Vertices[9].Position = FVector(IC, D1, CT);
	Vertices[10].Position = FVector(W1 - D2, W1 - CT, CT);
	Vertices[11].Position = FVector(W1, W1 - CT, CT);

	//Rotate verts based on cabinet angle
	Vertices[4].Position = RotateVertexAboutPoint(Vertices[4].Position, Vertices[1].Position, angle);
	Vertices[5].Position = RotateVertexAboutPoint(Vertices[5].Position, Vertices[1].Position, angle);
	Vertices[10].Position = RotateVertexAboutPoint(Vertices[10].Position, Vertices[1].Position, angle);
	Vertices[11].Position = RotateVertexAboutPoint(Vertices[11].Position, Vertices[1].Position, angle);
	/*
	Vertices[0].UV0 = FVector2D(0.0f, UVY);
	Vertices[1].UV0 = FVector2D(UVX, UVY);
	Vertices[2].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[3].UV0 = FVector2D(UVX, 0.0f);

	Vertices[4].UV0 = FVector2D(0.0f, UVY);
	Vertices[5].UV0 = FVector2D(UVX, UVY);
	Vertices[6].UV0 = FVector2D(0.0f, UVY - TKD);
	Vertices[7].UV0 = FVector2D(UVX, UVY - TKD);

	Vertices[8].UV0 = FVector2D(0.0f, UVY);
	Vertices[9].UV0 = FVector2D(UVX, UVY);
	Vertices[10].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[11].UV0 = FVector2D(UVX, 0.0f);
	*/
	CalculateOffset(Vertices, offset);

	//Bottom - Top
	Triangles.SetNum(24);

	Triangles[0] = 1;
	Triangles[1] = 5;
	Triangles[2] = 3;

	Triangles[3] = 3;
	Triangles[4] = 5;
	Triangles[5] = 4;

	Triangles[6] = 9;
	Triangles[7] = 11;
	Triangles[8] = 7;

	Triangles[9] = 10;
	Triangles[10] = 11;
	Triangles[11] = 9;

	Triangles[12] = 0;
	Triangles[13] = 1;
	Triangles[14] = 2;

	Triangles[15] = 2;
	Triangles[16] = 1;
	Triangles[17] = 3;

	Triangles[18] = 8;
	Triangles[19] = 7;
	Triangles[20] = 6;

	Triangles[21] = 9;
	Triangles[22] = 7;
	Triangles[23] = 8;

	GenerateMeshSection(0, vColor, Vertices, Triangles);
	/*
	Vertices[0].UV0 = FVector2D(UVY - TKD, 0.0f);
	Vertices[1].UV0 = FVector2D(UVY - TKD, 0.0f);
	Vertices[2].UV0 = FVector2D(0.0f, 0.0f);
	Vertices[3].UV0 = FVector2D(0.0f, 0.0f);

	Vertices[4].UV0 = FVector2D(UVY, TKH);
	Vertices[5].UV0 = FVector2D(UVY, TKH);
	Vertices[6].UV0 = FVector2D(UVY - TKD, TKH);
	Vertices[7].UV0 = FVector2D(UVY - TKD, TKH);

	Vertices[8].UV0 = FVector2D(UVY, UVZ);
	Vertices[9].UV0 = FVector2D(UVY, UVZ);
	Vertices[10].UV0 = FVector2D(0.0f, UVZ);
	Vertices[11].UV0 = FVector2D(0.0f, UVZ);
	*/
	//Left -  Right
	Triangles[0] = 2;
	Triangles[1] = 3;
	Triangles[2] = 8;

	Triangles[3] = 3;
	Triangles[4] = 9;
	Triangles[5] = 8;

	Triangles[6] = 3;
	Triangles[7] = 4;
	Triangles[8] = 9;

	Triangles[9] = 9;
	Triangles[10] = 4;
	Triangles[11] = 10;

	Triangles[12] = 6;
	Triangles[13] = 1;
	Triangles[14] = 0;

	Triangles[15] = 7;
	Triangles[16] = 1;
	Triangles[17] = 6;

	Triangles[18] = 7;
	Triangles[19] = 5;
	Triangles[20] = 1;

	Triangles[21] = 11;
	Triangles[22] = 5;
	Triangles[23] = 7;

	GenerateMeshSection(1, vColor, Vertices, Triangles);

}

void ACab_Parts_RT::GenerateCornerCabinetCornerBack(FVector size, float angle, UPARAM() FVector offset, UPARAM() bool createCollision,
	UPARAM() UMaterialInstance* mat, UPARAM() FLinearColor vertexColor, EUnitsType eType, bool LEdgeOffset, bool REdgeOffset, float UVScale)
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

	if (LEdgeOffset)
	{
		Vertices[2].Position = FVector(Vertices[2].Position.X - CalcBackEdgeOffset(sizeMod.Y, angle), Vertices[2].Position.Y, Vertices[2].Position.Z);
		Vertices[6].Position = FVector(Vertices[6].Position.X - CalcBackEdgeOffset(sizeMod.Y, angle), Vertices[6].Position.Y, Vertices[6].Position.Z);
	}

	if (REdgeOffset)
	{
		Vertices[3].Position = FVector(Vertices[3].Position.X + CalcBackEdgeOffset(sizeMod.Y, angle), Vertices[3].Position.Y, Vertices[3].Position.Z);
		Vertices[7].Position = FVector(Vertices[7].Position.X + CalcBackEdgeOffset(sizeMod.Y, angle), Vertices[7].Position.Y, Vertices[7].Position.Z);
	}

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

float ACab_Parts_RT::CalcCornerAngleDoorCenterVertexPos(float angle, float cabinetWidth, float CabinetDepth_2)
{
	float tempangle;

	if (angle > 180.0f)
	{
		tempangle = FMath::GetMappedRangeValue(FVector2D(180.0f, 270.0f), FVector2D(cabinetWidth, cabinetWidth + CabinetDepth_2), angle);
	}

	else
	{
		tempangle = FMath::GetMappedRangeValue(FVector2D(90.0f, 180.0f), FVector2D(cabinetWidth - CabinetDepth_2, cabinetWidth), angle);
	}
	GLog->Log(FString::SanitizeFloat(tempangle));
	return tempangle;
}

float ACab_Parts_RT::CalcBackEdgeOffset(float cabinetPanelThickness, float cabinetAngle)
{
	float outOffset;

	if (cabinetAngle > 90.0f && cabinetAngle <180.0f)
	{
		outOffset = 0.0f - (FMath::Tan(FMath::GetMappedRangeValueClamped(FVector2D(90.0f, 180.0f), FVector2D(45.0f, 0.0f), cabinetAngle) * (PI / 180.0f)) * cabinetPanelThickness);
	}

	else if (cabinetAngle >= 180.0f && cabinetAngle < 270.0f)
	{
		outOffset = 0.0f - (FMath::Tan(FMath::GetMappedRangeValueClamped(FVector2D(180.0f, 270.0f), FVector2D(0.0f, -45.0f), cabinetAngle) * (PI / 180.0f)) * cabinetPanelThickness);
	}

	else if (cabinetAngle >= 270.0f)
	{
		outOffset = 0.0f - (FMath::Tan(FMath::GetMappedRangeValueClamped(FVector2D(270.0f, 360.0f), FVector2D(-45.0f, -90.0f), cabinetAngle) * (PI / 180.0f)) * cabinetPanelThickness);
	}

	else
	{
		outOffset = 0.0f - (FMath::Tan(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 90.0f), FVector2D(90.0f, 45.0f), cabinetAngle) * (PI / 180.0f)) * cabinetPanelThickness);
	}

	return outOffset;
}
