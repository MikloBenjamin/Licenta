// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Algo/Rotate.h"
#include "Public/MonopolyProperty.h"
#include "Public/ParticipantPawn.h"
#include "Public/MonopolyHouseProperty.h"
#include "Public/Tax.h"
#include "Public/Railroad.h"
#include "Public/SecretCard.h"
#include "Public/ElectricAndWaterWorks.h"
#include "Public/Card.h"
#include "Public/Widgets/InitialWidget.h"
#include "Public/Widgets/InGameWidget.h"
#include "Public/Widgets/StartGameWidget.h"
#include "Public/Widgets/PlayWidget.h"
#include "Public/Widgets/OwnedPropertiesWidget.h"
#include "Public/Widgets/OwnedPropsPayRestWidget.h"
#include "Public/Widgets/BuyHouseWidget.h"
#include "Public/Widgets/CardsWidget.h"
#include "Public/Widgets/GameOverWidget.h"
#include "Public/PropertyHouse.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetArrayLibrary.h"
#include "MP_GameMode.generated.h"


/**
 * 
 */
UCLASS()
class LICENTA_API AMP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	private:
		void Log(FString log);
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaSeconds) override;
		virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
		FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSourceDir()) + TEXT("/DebugLogs.log");
		int ScreenDebugKey = 123456;
	public:
		UFUNCTION(BlueprintCallable, Category = "Default")
		void PayRest(AParticipantPawn* Player, int Rest, AParticipantPawn* Receiver = nullptr);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleRest(AParticipantPawn* Player, int Rest, AParticipantPawn* Receiver = nullptr);

		UFUNCTION(BlueprintCallable, Category="Default")
		void Initialize();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ClearRoundTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetRoundTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ClearDiceRollTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetDiceRollTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ClearRollDiceAnimationTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetRollDiceAnimationTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ClearUseCardTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetUseCardTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ClearSellForRestTimer();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetSellRestTimer();

		UFUNCTION(BlueprintImplementableEvent, Category = "Default")
		void BindPayRestButtons();

		UFUNCTION(BlueprintImplementableEvent, Category = "Default")
		void PlayDiceRollSound();

		UFUNCTION(BlueprintImplementableEvent, Category = "Default")
		void GenerateTilesForRestWidget();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void RecalculateRestInformation();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void ContinuePay();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void GeneratePlayers(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void StartGame(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void NextPlayer();

		UFUNCTION(BlueprintCallable, Category="Default")
		void NextPlayerTurn();

		UFUNCTION(BlueprintCallable, Category="Default")
		void ExecuteBotTurn();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* ExecutePlayerTurn();
	
		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleProperty(AMonopolyProperty* Property, AParticipantPawn* Player = nullptr);
	
		UFUNCTION(BlueprintCallable, Category = "Default")
		void UseCard(TArray<ACard*>& Cards);
	
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
		void BuyProperty(AMonopolyProperty* Property = nullptr, AParticipantPawn* Player = nullptr);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellProperty(const int Position, AParticipantPawn* Player = nullptr);

		UFUNCTION(BlueprintCallable, Category="Default")
		int Pay(const int Amount);

		UFUNCTION(BlueprintCallable, Category = "Default")
		bool UpgradePossible(AMonopolyProperty* Property, AParticipantPawn* Participant);

		UFUNCTION(BlueprintCallable, Category = "Default")
		bool DegradePossible(AMonopolyProperty* Property, AParticipantPawn* Participant);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void UpgradeProperty(AMonopolyProperty* Property = nullptr, AParticipantPawn* Player = nullptr);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellHouse(AMonopolyProperty* Property = nullptr, AParticipantPawn* Player = nullptr);

		UFUNCTION(BlueprintCallable, Category="Default")
		AParticipantPawn* GetParticipant();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* GetProperty(const int Position);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void CHEAT();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void CalculateCanBuySellHouseOrProperty();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void OfferTrade(
			AParticipantPawn* Player1,
			AParticipantPawn* Player2,
			FOffer offer
		);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellUnnecesaryPropertiesAndBuyProperty(AParticipantPawn* Player, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyHouseAI(AParticipantPawn* Player, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyPropertyAI(AParticipantPawn* Player, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyRailroadAI(AParticipantPawn* Player, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyElectricAI(AParticipantPawn* Player, AMonopolyProperty* Property);

		UFUNCTION(BlueprintCallable, Category = "Default")
		void HandleBotAI(AParticipantPawn* Player, AMonopolyProperty* Property);

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
		UOwnedPropsPayRestWidget* PayRestMenu;

		UPROPERTY(BlueprintReadWrite)
		UBuyHouseWidget* BuyHouseMenu;

		UPROPERTY(BlueprintReadWrite)
		UGameOverWidget* GameOverMenu;
	
		UPROPERTY(BlueprintReadOnly)
		int PlayerTurn;

		UPROPERTY(BlueprintReadWrite)
		TMap<int, FHouses> Houses;

		FTimerHandle RoundTimer;
		FTimerHandle DiceRollTimer;
		FTimerHandle RollDiceAnimationTimer;
		FTimerHandle UseCardTimer;
		FTimerHandle SellForRestTimer;
	private:
		int LastDiceRolled;
		bool Initialized = false;

		void GenerateHouses();
		void HandleOwnedProperty(AMonopolyProperty* Property, AParticipantPawn* Participant);
};
