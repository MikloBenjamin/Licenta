// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Money.h"
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

public:
	// PUBLIC NON-BP FUNCTIONS
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// PUBLIC BLUEPRINT FUNCTIONS -----------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	int GetPlayerPosition() const;

	UFUNCTION(BlueprintCallable)
	UMoney* GetMoney() const;

	UFUNCTION(BlueprintCallable, Category="Default")
	int Pay(const int Amount);

	UFUNCTION(BlueprintCallable, Category="Default")
	int Receive(const int Amount);

	UFUNCTION(BlueprintCallable, Category="Default")
	void Initialize(FString PartName, UStaticMesh* StaticMesh, UMaterial* Material);
	
	UFUNCTION(BlueprintCallable, Category="Default")
	bool IsBot() const
	{
		return IsAI;
	}

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
};
