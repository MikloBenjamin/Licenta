// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonopolyProperty.h"
#include "Railroad.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API ARailroad : public AMonopolyProperty
{
	GENERATED_BODY()
public:
	ARailroad* Initialize(
		const int Pos, const FString Name, const EActions Action, FString AssetPath = "", AParticipantPawn* Player = nullptr);

	FString PriceToPay(AParticipantPawn* PropertyOwnerParticipant);

	FString PriceToBuy();

	FString PriceToSell();
};
