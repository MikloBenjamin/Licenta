// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PropertyHouse.generated.h"

class AParticipantPawn;

/**
 * 
 */
UCLASS()
class LICENTA_API APropertyHouse : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	APropertyHouse();

	UPROPERTY(BlueprintReadWrite)
	AParticipantPawn* prop_owner;
};
