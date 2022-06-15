// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonopolyProperty.h"
#include "MonopolyHouseProperty.generated.h"

/**
 * 
 */
UCLASS()
// class LICENTA_API UMonopolyHouseProperty : public UMonopolyProperty
class LICENTA_API AMonopolyHouseProperty : public AMonopolyProperty
{
	GENERATED_BODY()
	protected:
		UPROPERTY(BlueprintReadOnly)
		FBuyPrice BuyPrice;
		
		UPROPERTY(BlueprintReadOnly)
		FPayPrice PayPrice;

		UPROPERTY(BlueprintReadOnly)
		int Houses;

		UPROPERTY(BlueprintReadOnly)
		EPropGroups PropGroup;

	public:
		AMonopolyHouseProperty* Initialize(
			const int Pos, const FString Name, const EActions Action, FString AssetPath = "",
			AParticipantPawn* Player = nullptr, FBuyPrice Buy = FBuyPrice{0,0},
			FPayPrice Pay = FPayPrice{0,0, 0, 0, 0, 0}, EPropGroups group = EPropGroups::Brown);

		FString PriceToPay(AParticipantPawn* Participant);

		FString PriceToBuy();

		FString PriceToSell();

		FString UpgradePrice();

		int GetHouses() const { return Houses; }

		void ResetInit();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void BuyHouse();

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SellHouse();

		UFUNCTION(BlueprintCallable, Category = "Default")
		EPropGroups GetPropGroup() const { return PropGroup; }

		UPROPERTY(BlueprintReadWrite)
			bool CanBuyHouse = false;

		UPROPERTY(BlueprintReadWrite)
			bool CanSellHouse = false;

		UPROPERTY(BlueprintReadWrite)
			bool CanSellProperty = false;
};
