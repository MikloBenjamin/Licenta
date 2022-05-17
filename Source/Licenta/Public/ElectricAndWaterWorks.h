// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonopolyProperty.h"
#include "ElectricAndWaterWorks.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API AElectricAndWaterWorks : public AMonopolyProperty
{
	GENERATED_BODY()
public:
	AElectricAndWaterWorks* Initialize(
		const int Pos, const FString Name, const EActions Action, FString AssetPath = "", AParticipantPawn* Player = nullptr);

	FString PriceToPayUtility(AParticipantPawn* PropertyOwnerParticipant, int DiceRolls);

	FString PriceToBuy();

	FString PriceToSell();
};
