// Fill out your copyright notice in the Description page of Project Settings.

#include "Procedural_Cabinet.h"


// Sets default values
AProcedural_Cabinet::AProcedural_Cabinet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CabinetHeight = 36.0f;
	CabinetWidth = 36.0f;
	CabinetDepth = 23.25f;
	CabinetPanelThickness = 0.75f;

	CabinetAngle = 90.0f;

	TKHeight = 4.0f;
	TKDepth = 4.0f;

	ScribeWidth = 2.0f;

	DrawerFrontHeight = 6.0f;
	DoorGap = .125f;

	eType = EUnitsType::Pro_AmericanStandard;

	FinishLeft = 0.0f;
	FinishRight = 0.0f;

	DynamicMaterialInst = UMaterialInstanceDynamic::Create(Material, NULL);
	UVScale = 32.0f;

	Root = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("RootComponent"));
	RootComponent = Root;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Pro_Furniture/Blueprints/Doors/Procedural_Cabinet_Door.Procedural_Cabinet_Door'"));
	if (ItemBlueprint.Object) {
		Procedural_Cabinet_Door = (UClass*)ItemBlueprint.Object->GeneratedClass;
		//Procedural_Cabinet_Door* Door = ConstructObject(AProcedural_Cabinet*);
	}
}

void AProcedural_Cabinet::BeginDestroy()
{
	GLog->Log("Destruction");

	DestroyChildren();

	Super::BeginDestroy();
}

void AProcedural_Cabinet::OnConstruction(const FTransform & Transform)
{
	//GLog->Log("Construction");
	if (autoGenerate)
	{
		GenerateCabinet();
	}

	else
	{
		DestroyChildren();
	}
}


// Called when the game starts or when spawned
void AProcedural_Cabinet::BeginPlay()
{
	Super::BeginPlay();

	if (autoGenerate)
	{
		GenerateCabinet();
	}
}

// Called every frame
void AProcedural_Cabinet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcedural_Cabinet::DestroyChildren()
{
	//https://answers.unrealengine.com/questions/357329/destroying-spawned-objects-ondestroy-in-editor.html
	TArray<AActor*> TheAttached;
	this->GetAttachedActors(TheAttached);
	UE_LOG(LogTemp, Log, TEXT("The attached.Num is %d"), TheAttached.Num());
	UE_LOG(LogTemp, Log, TEXT("this->Children.Num is %d"), this->Children.Num());

	for (int i = 0; i < TheAttached.Num(); i++)
	{
		TheAttached[i]->Destroy();
	}
}

//Vector paneloffset = FVector(cos(offset.Z * PI / 180.0) * (offset.X - offset.X) - sin(offset.Z * PI / 180.0) * (0.f - offset.Y) + offset.X,
//tcos(offset.Z * PI / 180.0) * (0.f - offset.Y) - sin(offset.Z * PI / 180.0) * (offset.X - offset.X) + 0.f, 0.f) * scaleMod;
FVector AProcedural_Cabinet::GetCornerRightPanelOffset()
{
	return FVector( CabinetWidth + (0.0f - ((0.0f - (CabinetWidth - CabinetPanelThickness)) * (FMath::Sin((180 - CabinetAngle + 90) * (PI / 180.0f )) ))),
		(0.0f - (CabinetWidth - CabinetPanelThickness)) * (FMath::Cos((180 - CabinetAngle + 90) * (PI / 180.0f))),
		0.0f) * sMod;
}

void AProcedural_Cabinet::GenerateCabinet()
{
	//Must destroy all child actors before making new ones - These should be autodestroyed but are not
	DestroyChildren();

	switch (cType)
	{
	default:
		UE_LOG(LogTemp, Warning, TEXT("Invalid cabinet type - Procedural_Cabinet.cpp - GenerateCabinet()"));
		break;

	case ECabinetType::Base:
	{
		Generate_BaseCabinet();
		break;
	}
	case ECabinetType::BaseCorner_Straight:
	{
		Generate_BaseCornerStraight_Cabinet();
		break;
	}

	case ECabinetType::BaseCorner_Angled:
	{
		Generate_BaseCornerAngled_Cabinet();
		break;
	}
	case ECabinetType::Wall:
	{
		Generate_WallCabinet();
		break;
	}
	case ECabinetType::WallCorner_Straight:
	{
		break;
	}
	case ECabinetType::WallCorner_Angled:
	{
		break;
	}
	}
}

void AProcedural_Cabinet::Generate_BaseCabinet()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	const UWorld* world = GetWorld();

	if (world)
	{
		FVector size = FVector(0.0f, 0.0f, 0.0f);
		FVector offset = FVector(0.0f, 0.0f, 0.0f);

		//https://answers.unrealengine.com/questions/566413/actor-spawns-with-components-already-ispendingkill.html

		//Left Side
		ACab_Parts_RT* MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		GLog->Log("Object has been created!");
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);

		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Cannot register directly from here since procecduralcabinet is not a child class of runtimemeshactor
		//MyObject->Register();

		//Right Side
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);
		offset = FVector(CabinetWidth - CabinetPanelThickness, 0.0f, 0.0f);

		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Bottom
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, 0.0f, TKHeight);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Back
		float backThickness = CabinetPanelThickness / 3;				//We may add this an adjustable variable later (I typically use 3/4" plywood for cabinet sides with 1/4" for the backs.
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), backThickness, CabinetHeight - TKHeight - CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, CabinetPanelThickness, TKHeight + CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Rails
		float railWidth = 3.0f;

		//Back Rail
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetPanelThickness, railWidth);
		offset = FVector(CabinetPanelThickness, 0.0f, CabinetHeight - railWidth);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Back Rail Top
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), railWidth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, CabinetPanelThickness + backThickness, CabinetHeight - CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Front Rail Top
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), railWidth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, CabinetDepth - railWidth, CabinetHeight - CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Front Rail Bottom
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), railWidth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, CabinetDepth - railWidth, CabinetHeight - DrawerFrontHeight - ((CabinetPanelThickness + DoorGap) / 2));

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//If has double Door
		//Rail - Door Splitter
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth - CabinetPanelThickness - backThickness, DoorGap + DrawerFrontHeight - CabinetPanelThickness - ((CabinetPanelThickness + DoorGap) / 2));
		offset = FVector((CabinetWidth - CabinetPanelThickness) / 2, CabinetPanelThickness + backThickness, CabinetHeight - DrawerFrontHeight - ((CabinetPanelThickness + DoorGap) / 2) + CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//ToeKick
		size = FVector(CabinetWidth + FinishLeft + FinishRight, CabinetPanelThickness, TKHeight);
		offset = FVector(-FinishLeft, CabinetDepth - TKDepth, 0.0f);

		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Scribe Left
		if (FinishLeft > 0)
		{
			size = FVector(FinishLeft, CabinetPanelThickness, CabinetHeight - TKHeight);
			offset = FVector(-FinishLeft, CabinetDepth - CabinetPanelThickness, TKHeight);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);


			size = FVector(FinishLeft, TKDepth - CabinetPanelThickness, CabinetPanelThickness);
			offset = FVector(-FinishLeft, CabinetDepth - TKDepth, TKHeight);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);
		}

		//Scribe Right
		if (FinishRight > 0)
		{
			size = FVector(FinishRight, CabinetPanelThickness, CabinetHeight - TKHeight);
			offset = FVector(CabinetWidth, CabinetDepth - CabinetPanelThickness, TKHeight);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);


			size = FVector(FinishRight, TKDepth - CabinetPanelThickness, CabinetPanelThickness);
			offset = FVector(CabinetWidth, CabinetDepth - TKDepth, TKHeight);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);
		}

	}
}

void AProcedural_Cabinet::Generate_WallCabinet()
{

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	const UWorld* world = GetWorld();

	if (world)
	{
		FVector size = FVector(0.0f, 0.0f, 0.0f);
		FVector offset = FVector(0.0f, 0.0f, 0.0f);

		//https://answers.unrealengine.com/questions/566413/actor-spawns-with-components-already-ispendingkill.html

		//Left Side
		ACab_Parts_RT* MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		GLog->Log("Object has been created!");
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Cannot register directly from here since procecduralcabinet is not a child class of runtimemeshactor
		//MyObject->Register();

		//Right Side
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);
		offset = FVector(CabinetWidth - CabinetPanelThickness, 0.0f, 0.0f);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Bottom
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, 0.0f, 0.0f);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Top
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(CabinetPanelThickness, 0.0f, CabinetHeight - CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Back
		float backThickness = CabinetPanelThickness / 3;				//We may add this an adjustable variable later (I typically use 3/4" plywood for cabinet sides with 1/4" for the backs.
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), backThickness, CabinetHeight - (CabinetPanelThickness * 2));
		offset = FVector(CabinetPanelThickness, CabinetPanelThickness, CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);

		//Rails
		float railWidth = 3.0f;

		//Back Rail
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetPanelThickness, railWidth);
		offset = FVector(CabinetPanelThickness, 0.0f, CabinetHeight - railWidth - CabinetPanelThickness);

		MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);


		//Scribe Left
		if (FinishLeft > 0)
		{
			size = FVector(FinishLeft, CabinetPanelThickness, CabinetHeight);
			offset = FVector(-FinishLeft, CabinetDepth - CabinetPanelThickness, 0.0f);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);
		}

		//Scribe Right
		if (FinishRight > 0)
		{
			size = FVector(FinishRight, CabinetPanelThickness, CabinetHeight);
			offset = FVector(CabinetWidth, CabinetDepth - CabinetPanelThickness, 0.0f);

			MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
			MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			MyObject->GenerateCube(size, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, UVScale);
		}

	}
}

void AProcedural_Cabinet::Generate_BaseCornerStraight_Cabinet()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	const UWorld* world = GetWorld();

	if (world)
	{
		FVector size = FVector(0.0f, 0.0f, 0.0f);
		FVector offset = FVector(0.0f, 0.0f, 0.0f);

		//https://answers.unrealengine.com/questions/566413/actor-spawns-with-components-already-ispendingkill.html

		//Left Side
		ACab_Parts_RT* MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		GLog->Log("Object has been created!");
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);

		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Cannot register directly from here since procecduralcabinet is not a child class of runtimemeshactor
		//MyObject->Register();

		//Right Side
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, GetCornerRightPanelOffset(), FRotator(0.0f, 180.0f - CabinetAngle, 0.0f), SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);
		//offset = FVector(CabinetWidth - CabinetPanelThickness, 0.0f, 0.0f);
		offset = FVector::ZeroVector;
		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Bottom
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(0.0f, 0.0f, TKHeight);

		MyObject->GenerateCornerCabinetBottomStraight(size.Y, size.Y, CabinetWidth, CabinetWidth, offset, false, DynamicMaterialInst, FLinearColor::Black,
			CabinetAngle, CabinetPanelThickness, eType, UVScale);

		//Top
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(0.0f, 0.0f, CabinetHeight - CabinetPanelThickness);

		MyObject->GenerateCornerCabinetBottomStraight(size.Y, size.Y, CabinetWidth, CabinetWidth, offset, false, DynamicMaterialInst, FLinearColor::Black,
			CabinetAngle, CabinetPanelThickness, eType, UVScale);

		//Back_L
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - CabinetPanelThickness, CabinetPanelThickness, CabinetHeight - (CabinetPanelThickness * 2) - TKHeight);
		offset = FVector(CabinetPanelThickness, 0.0f, TKHeight + CabinetPanelThickness);
		
		MyObject->GenerateCornerCabinetCornerBack(size, CabinetAngle, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, false, true, UVScale);
		//Back_R
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector(CabinetWidth, 0.0f, 0.0f) * sMod, FRotator(0.0f, 180.0f - CabinetAngle, 0.0f), SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - CabinetPanelThickness, CabinetPanelThickness, CabinetHeight - (CabinetPanelThickness * 2) - TKHeight);
		offset = FVector(0.0f, 0.0f, TKHeight + CabinetPanelThickness);

		MyObject->GenerateCornerCabinetCornerBack(size, CabinetAngle, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, true, false, UVScale);
	}
}

void AProcedural_Cabinet::Generate_BaseCornerAngled_Cabinet()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	const UWorld* world = GetWorld();

	if (world)
	{
		FVector size = FVector(0.0f, 0.0f, 0.0f);
		FVector offset = FVector(0.0f, 0.0f, 0.0f);

		//https://answers.unrealengine.com/questions/566413/actor-spawns-with-components-already-ispendingkill.html

		//Left Side
		ACab_Parts_RT* MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		GLog->Log("Object has been created!");
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);

		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Cannot register directly from here since procecduralcabinet is not a child class of runtimemeshactor
		//MyObject->Register();

		//Right Side
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, GetCornerRightPanelOffset(), FRotator(0.0f, 180.0f - CabinetAngle, 0.0f), SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetPanelThickness, CabinetDepth, CabinetHeight);
		//offset = FVector(CabinetWidth - CabinetPanelThickness, 0.0f, 0.0f);
		offset = FVector::ZeroVector;
		MyObject->GenerateCabinetSide(size, offset, false, DynamicMaterialInst, FLinearColor::Black,
			TKHeight, TKDepth, 0.0f, 0.0f, eType, UVScale);

		//Bottom
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(0.0f, 0.0f, TKHeight);

		MyObject->GenerateCornerCabinetBottomAngled(size.Y, size.Y, CabinetWidth, CabinetWidth, offset, false, DynamicMaterialInst, FLinearColor::Black,
			CabinetAngle, CabinetPanelThickness, eType, UVScale);

		//Top
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - (CabinetPanelThickness * 2), CabinetDepth, CabinetPanelThickness);
		offset = FVector(0.0f, 0.0f, CabinetHeight - CabinetPanelThickness);

		MyObject->GenerateCornerCabinetBottomAngled(size.Y, size.Y, CabinetWidth, CabinetWidth, offset, false, DynamicMaterialInst, FLinearColor::Black,
			CabinetAngle, CabinetPanelThickness, eType, UVScale);

		//Back_L
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - CabinetPanelThickness, CabinetPanelThickness, CabinetHeight - (CabinetPanelThickness * 2) - TKHeight);
		offset = FVector(CabinetPanelThickness, 0.0f, TKHeight + CabinetPanelThickness);

		MyObject->GenerateCornerCabinetCornerBack(size, CabinetAngle, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, false, true, UVScale);
		//Back_R
		MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector(CabinetWidth, 0.0f, 0.0f) * sMod, FRotator(0.0f, 180.0f - CabinetAngle, 0.0f), SpawnInfo);
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		size = FVector(CabinetWidth - CabinetPanelThickness, CabinetPanelThickness, CabinetHeight - (CabinetPanelThickness * 2) - TKHeight);
		offset = FVector(0.0f, 0.0f, TKHeight + CabinetPanelThickness);

		MyObject->GenerateCornerCabinetCornerBack(size, CabinetAngle, offset, false, DynamicMaterialInst, FLinearColor::Black, eType, true, false, UVScale);
	}
}

void AProcedural_Cabinet::SpawnDoor()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	UWorld* const World = GetWorld();
	if (World) {

	//	Procedural_Cabinet_Door* Door = GetWorld()->SpawnActor<AProcedural_Cabinet>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

	//	GLog->Log("Object has been created!");
	//	Door->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

