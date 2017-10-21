// Fill out your copyright notice in the Description page of Project Settings.

#include "Procedural_CabinetDoor.h"


// Sets default values
AProcedural_CabinetDoor::AProcedural_CabinetDoor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Pro_Furniture/Blueprints/Doors/Procedural_Cabinet_Door.Procedural_Cabinet_Door'"));
	if (ItemBlueprint.Object) {
		Procedural_Cabinet_Door = (UClass*)ItemBlueprint.Object->GeneratedClass;
		Spawn();
	}

}

// Called when the game starts or when spawned
void AProcedural_CabinetDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProcedural_CabinetDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcedural_CabinetDoor::Spawn()
{
	/*
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		AItem* DroppedItem = World->SpawnActor<ASurItem>(MyItemBlueprint, Location, Rotation, SpawnParams);
		ACab_Parts_RT* MyObject = GetWorld()->SpawnActor<ACab_Parts_RT>(partOne, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		GLog->Log("Object has been created!");
		MyObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
	*/
}
