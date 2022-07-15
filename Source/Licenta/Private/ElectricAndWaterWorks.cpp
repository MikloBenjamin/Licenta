// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricAndWaterWorks.h"
#include <Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>

AElectricAndWaterWorks* AElectricAndWaterWorks::Initialize(
	const int Pos, const FString Name, const EActions Action, FString AssetPath, AParticipantPawn* Player)
{
	Super::Initialize(Pos, Name, Action, AssetPath, Player, true);
	PropertyType = EType::Utility;
	return this;
}

FString AElectricAndWaterWorks::PriceToPay(AParticipantPawn* PropertyOwnerParticipant)
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(PropertyOwnerParticipant->DiceRoll * (PropertyOwnerParticipant->UtilitiesOwned < 2 ? 4 : 10)));
}

FString AElectricAndWaterWorks::PriceToBuy()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(150));
}


FString AElectricAndWaterWorks::PriceToSell()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(75));
}
