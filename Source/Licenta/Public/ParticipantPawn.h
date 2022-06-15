// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Money.h"
#include "Card.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "ParticipantPawn.generated.h"

UCLASS()
class LICENTA_API AParticipantPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	// CONSTRUCTORS
	AParticipantPawn();

	UFUNCTION(BlueprintCallable, Category = "Default")
	virtual int Play();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	int Rest = 0;

protected:
	// PROTECTED NON-BP FUNCTIONS
	virtual void BeginPlay() override;

	void RestrainPosition();
	
	// PROTECTED BLUEPRINT FUNCTIONS
	UFUNCTION(BlueprintCallable)
	FRotator GetCameraDestinationPosition();

	UFUNCTION(BlueprintCallable)
	void MoveCamera();
	
	UFUNCTION(BlueprintCallable)
	void MovePawn(const int MoveBy);

	// PROTECTED VARIABLES
	int Position = 0;
	bool IsAI = false;
	TArray<FVector> Destinations;
	float WaitTime = 0.21;

public:
	int JailedFor = 0;
	// PUBLIC NON-BP FUNCTIONS
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// PUBLIC BLUEPRINT FUNCTIONS -----------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void Move(int positions);

	UFUNCTION(BlueprintCallable)
	int GetPlayerPosition() const;

	UFUNCTION(BlueprintCallable)
	UMoney* GetMoney() const;

	UFUNCTION(BlueprintCallable, Category="Default")
	int Pay(const int Amount, AParticipantPawn* To = nullptr);

	UFUNCTION(BlueprintCallable, Category="Default")
	int Receive(const int Amount);

	UFUNCTION(BlueprintCallable, Category="Default")
	void Initialize(FString PartName, UStaticMesh* StaticMesh, UMaterial* Material);
	
	UFUNCTION(BlueprintCallable, Category="Default")
	bool IsBot() const
	{
		return IsAI;
	}

	UFUNCTION(BlueprintCallable, Category = "Default")
	bool GetRolled() const;


	UFUNCTION(BlueprintCallable, Category = "Default")
	void SetRolled(bool value);

	// --------------------------------------------------------------------------------------------
	// PUBLIC VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	UStaticMeshComponent *RComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	USpringArmComponent *SArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	UCameraComponent *CameraC;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	UMoney* Money;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default")
	FString ParticipantName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	int RailroadsOwned;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	int UtilitiesOwned;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	bool Rolled;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	UMaterial* color;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	ACard* Card;
};
