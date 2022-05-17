// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticipantPawn.h"

// Sets default values
AParticipantPawn::AParticipantPawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Participant Constructor"));
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerSmComponent"));
	SArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerSaComponent"));
	CameraC = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamComponent"));
	
	RComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	RComponent->SetWorldScale3D(FVector(2, 2, 2));
	RComponent->SetRelativeScale3D(FVector(2, 2, 2));
	SArm->SetupAttachment(RComponent);
	CameraC->SetupAttachment(SArm, USpringArmComponent::SocketName);
	
	SArm->bEnableCameraLag = true;
	SArm->TargetArmLength = 1500.0f;
	SArm->CameraLagSpeed = 3.0f;
	SArm->SetRelativeLocation(FVector(25, 25, 50));
	SetRootComponent(RComponent);

	RailroadsOwned = 0;
	UtilitiesOwned = 0;
}

void AParticipantPawn::Initialize(FString PartName, UStaticMesh* StaticMesh, UMaterial* Material)
{
	color = Material;
	StaticMesh->SetMaterial(0, Material);
	RComponent->SetStaticMesh(StaticMesh);
	RComponent->SetWorldScale3D(FVector(1, 1, 2));
	RComponent->SetRelativeScale3D(FVector(1, 1, 2));
	ParticipantName = PartName;
	Money = NewObject<UMoney>(this, TEXT("Money"));
	Money->PrepareCppStructOps();
	if (!IsAI)
	{
		MoveCamera();
	}
	else
	{
		RComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	}
}

// Called when the game starts or when spawned
void AParticipantPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticipantPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParticipantPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AParticipantPawn::RestrainPosition()
{
	Position += 1;
	if (Position > 39)
	{
		Position -= 40;
	}
	else if (Position < 0)
	{
		Position = 0;
	}
}

FRotator AParticipantPawn::GetCameraDestinationPosition()
{
	// FRotator(Y, Z, X)
	FRotator CameraPosition = FRotator(235, 45, 180);
	if (Position >= 1 && Position <= 9)
	{
		CameraPosition = FRotator(235, 90, 180);
	}
	else if (Position == 10)
	{
		CameraPosition = FRotator(235, 135, 180);
	}
	else if (Position >= 11 && Position <= 19)
	{
		CameraPosition = FRotator(235, 180, 180);
	}
	else if (Position == 20)
	{
		CameraPosition = FRotator(235, 225, 180);
	}
	else if (Position >= 21 && Position <= 29)
	{
		CameraPosition = FRotator(235, 270, 180);
	}
	else if (Position == 30)
	{
		CameraPosition = FRotator(235, 315, 180);
	}
	else if (Position >= 31 && Position <= 39)
	{
		CameraPosition = FRotator(235, 0, 180);
	}

	return CameraPosition;
}

void AParticipantPawn::MoveCamera()
{
	const FRotator CameraPosition = GetCameraDestinationPosition();
	SArm->SetRelativeRotation(CameraPosition);
}

void AParticipantPawn::MovePawn(const int MoveBy)
{
	FVector PlayerPosition = GetActorLocation();
	for(int Itr = 0; Itr < MoveBy; Itr++)
	{
		if (Position < 10)
		{
			PlayerPosition -= FVector(400, 0, 0);
		}
		else if(Position < 20)
		{
			PlayerPosition -= FVector(0, 400, 0);
		}
		else if(Position < 30)
		{
			PlayerPosition += FVector(400, 0, 0);
		}
		else if(Position < 40)
		{
			PlayerPosition += FVector(0, 400, 0);
		}
		RestrainPosition();
	}
	SetActorLocation(PlayerPosition);
	if (!IsAI) MoveCamera();
}

void AParticipantPawn::SetRolled(bool value)
{
	Rolled = value;
}

bool AParticipantPawn::GetRolled() const
{
	return Rolled;
}

int AParticipantPawn::Pay(const int Amount)
{
	return Money->Calculate(Amount);
}

int AParticipantPawn::GetPlayerPosition() const
{
	return Position;
}

UMoney* AParticipantPawn::GetMoney() const
{
	return Money;
}

int AParticipantPawn::Receive(int Amount) {
	return Money->Increase(Amount);
}
