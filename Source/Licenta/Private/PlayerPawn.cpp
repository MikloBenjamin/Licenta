// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn() : AParticipantPawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Constructor"));
	IsAI = false;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*int APlayerPawn::Play()
{
	int DiceRoll = FMath::RandRange(1, 6) + FMath::RandRange(1, 6);
	if (DiceRoll == 12)
	{
		JailedFor = 0;
	}
	else if (JailedFor > 3)
	{
		JailedFor--;
		return DiceRoll;
	}
	MoveCamera();
	MovePawn(DiceRoll);
	return DiceRoll;
}*/


