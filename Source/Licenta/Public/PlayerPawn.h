// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticipantPawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class LICENTA_API APlayerPawn : public AParticipantPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	bool TurnEnded;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//virtual int Play() override;

	UFUNCTION(BlueprintCallable)
	void CheatMove()
	{
		MoveCamera();
		MovePawn(30);
	}
	
};
