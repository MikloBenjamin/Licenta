// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Constructor"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsAI = true;
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*int AAIPawn::Play()
{
	int DiceRoll = FMath::RandRange(1, 6) + FMath::RandRange(1, 6);
	MoveCamera();
	MovePawn(DiceRoll);
	return DiceRoll;
}*/

