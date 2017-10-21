// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Procedural_CabinetDoor.generated.h"

UCLASS(Blueprintable)
class PROCEDURAL_FURNITURE_API AProcedural_CabinetDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedural_CabinetDoor(const FObjectInitializer& ObjectInitializer);

	//https://answers.unrealengine.com/questions/53689/spawn-blueprint-from-c.html
	TSubclassOf<class AProcedural_CabinetDoor> Procedural_Cabinet_Door;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Spawn();
	
	
};
