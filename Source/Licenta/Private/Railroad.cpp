// Fill out your copyright notice in the Description page of Project Settings.


#include "Railroad.h"
#include <Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>

ARailroad* ARailroad::Initialize(
	const int Pos, const FString Name, const EActions Action, FString AssetPath, AParticipantPawn* Player)
{
	Super::Initialize(Pos, Name, Action, AssetPath, Player, true);
	PropertyType = EType::Railroad;
	return this;
}

FString ARailroad::PriceToPay(AParticipantPawn* PropertyOwnerParticipant)
{
	int ToPay = 25;
	for (int i = 0; i < PropertyOwnerParticipant->RailroadsOwned; i++)
	{
		ToPay *= 2;
	}
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(ToPay));
}

FString ARailroad::PriceToBuy()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(200));
}

FString ARailroad::PriceToSell()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(100));
}