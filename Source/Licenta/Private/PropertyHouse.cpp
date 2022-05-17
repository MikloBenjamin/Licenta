// Fill out your copyright notice in the Description page of Project Settings.


#include "PropertyHouse.h"

APropertyHouse::APropertyHouse()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/CustomMeshes/PropertyHouse"));
	if (Mesh.Object)
	{
		UE_LOG(LogTemp, Log, TEXT("PropertyHouse FOUND, setting mesh"));
		GetStaticMeshComponent()->SetStaticMesh(Mesh.Object);
		GetStaticMeshComponent()->SetWorldScale3D(FVector(0.3, 0.5, 0.5));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("PropertyHouse not found, path wrong?"));
	}
}
