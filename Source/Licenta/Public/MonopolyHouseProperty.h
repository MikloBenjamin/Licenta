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

	public:
		AMonopolyHouseProperty* Initialize(
			const FString Name, const EActions Action, FString AssetPath = "",
			AParticipantPawn* Player = nullptr, FBuyPrice Buy = FBuyPrice{0,0},
			FPayPrice Pay = FPayPrice{0,0, 0, 0, 0, 0});

		FString PriceToPay(AParticipantPawn* Participant);

		FString PriceToBuy();

		FString PriceToSell();

		FString UpgradePrice();

		void ResetInit();
};
