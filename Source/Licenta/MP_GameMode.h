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
#include "Public/OwnedPropertiesWidget.h"
#include "Public/BuyHouseWidget.h"
#include "Public/PropertyHouse.h"
#include "Blueprint/UserWidget.h"
#include "MP_GameMode.generated.h"

USTRUCT(BlueprintType)
struct FHouses
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	EPropGroups group;

	UPROPERTY(VisibleAnywhere)
	TArray<APropertyHouse*> houses;
};

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
		void ShowPropertiesMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HidePropertiesMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ShowSameGroupMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HideSameGroupMenu();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyProperty();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellProperty(const int Position);

		UFUNCTION(BlueprintCallable, Category="Default")
		int Pay(const int Amount);

		UFUNCTION(BlueprintCallable, Category = "Default")
		bool UpgradePossible(AMonopolyProperty* Property, AParticipantPawn* Participant);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void UpgradeProperty(AMonopolyProperty* Property = nullptr);

		UFUNCTION(BlueprintCallable, Category="Default")
		AParticipantPawn* GetParticipant();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* GetProperty(const int Position);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void CHEAT();

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

		UPROPERTY(BlueprintReadWrite)
		UOwnedPropertiesWidget* OwnedPropertiesMenu;

		UPROPERTY(BlueprintReadWrite)
		UBuyHouseWidget* BuyHouseMenu;
	
		UPROPERTY(BlueprintReadOnly)
		int PlayerTurn;

		UPROPERTY(BlueprintReadWrite)
		TMap<int, FHouses> Houses;
	private:
		int LastDiceRolled;

		void GenerateHouses();
		void HandleOwnedProperty(AMonopolyProperty* Property, AParticipantPawn* Participant);
};
