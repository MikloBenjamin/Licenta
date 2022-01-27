// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/MonopolyProperty.h"
#include "Public/ParticipantPawn.h"
#include "Public/MonopolyHouseProperty.h"
#include "Public/Tax.h"
#include "Public/Railroad.h"
#include "Public/SecretCard.h"
#include "Public/ElectricAndWaterWorks.h"
#include "Public/Actions.h"
#include "Public/Card.h"
#include "Public/InitialWidget.h"
#include "Public/InGameWidget.h"
#include "Public/StartGameWidget.h"
#include "Public/PlayWidget.h"
#include "Blueprint/UserWidget.h"
#include "MP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API AMP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	public:
		UFUNCTION(BlueprintCallable, Category="Default")
		void Initialize();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void GeneratePlayers(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void StartGame(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials);

		UFUNCTION(BlueprintCallable, Category="Default")
		void NextPlayerTurn();

		UFUNCTION(BlueprintCallable, Category="Default")
		void ExecuteBotTurn();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* ExecutePlayerTurn();
	
		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleShowStartMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleBackToInitialMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandlePlayMenu(bool StartTurn, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandlePropertyInfo(AMonopolyProperty* Property, AParticipantPawn* Participant);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleMoneyInfo(UMoney* PlayerMoney);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyProperty();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellProperty();

		UFUNCTION(BlueprintCallable, Category="Default")
		int Pay(const int Amount);

		UFUNCTION(BlueprintCallable, Category="Default")
		AParticipantPawn* GetParticipant();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* GetProperty(const int Position);

		// GAMEMODE PROPERTIES
		
		UPROPERTY(BlueprintReadWrite)
		TArray<AParticipantPawn*> Players;

		UPROPERTY(BlueprintReadWrite)
		TArray<AMonopolyProperty*> MonopolyProperties;
		
		UPROPERTY(BlueprintReadWrite)
		TArray<ACard*> ChanceCards;
	
		UPROPERTY(BlueprintReadWrite)
		TArray<ACard*> ChestCards;

		UPROPERTY(BlueprintReadWrite)
		UInitialWidget* InitialMenu;

		UPROPERTY(BlueprintReadWrite)
		UPlayWidget* PlayMenu;

		UPROPERTY(BlueprintReadWrite)
		UInGameWidget* InGameMenu;

		UPROPERTY(BlueprintReadWrite)
		UStartGameWidget* StartMenu;
	
		UPROPERTY(BlueprintReadOnly)
		int PlayerTurn;
	private:
		int LastDiceRolled;

		void HandleOwnedProperty(AMonopolyProperty* Property, AParticipantPawn* Participant);
};
