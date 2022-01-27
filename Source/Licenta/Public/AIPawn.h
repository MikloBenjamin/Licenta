// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "ParticipantPawn.h"
#include "AIPawn.generated.h"

UCLASS()
class LICENTA_API AAIPawn : public AParticipantPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// PUBLIC BLUEPRINT FUNCTIONS
	UFUNCTION(BlueprintCallable, Category="Default")
	int Play();
};
