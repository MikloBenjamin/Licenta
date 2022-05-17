// Fill out your copyright notice in the Description page of Project Settings.


#include "MonopolyHouseProperty.h"
#include <Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>

AMonopolyHouseProperty* AMonopolyHouseProperty::Initialize(
	const int Pos, const FString Name, const EActions Action, FString AssetPath,
	AParticipantPawn* Player, FBuyPrice Buy, FPayPrice Pay, EPropGroups group)
{
	Super::Initialize(Pos, Name, Action, AssetPath, Player, true);
	BuyPrice = Buy;
	PayPrice = Pay;
	Houses = 0;
	PropertyType = EType::Property;
	PropGroup = group;
	return this;
}

FString AMonopolyHouseProperty::PriceToPay(AParticipantPawn* Participant)
{
	int ToPay = 0;
	switch (Houses)
	{
	case 1:
		ToPay = PayPrice.OneHouse;
		break;
	case 2:
		ToPay = PayPrice.TwoHouse;
		break;
	case 3:
		ToPay = PayPrice.ThreeHouse;
		break;
	case 4:
		ToPay = PayPrice.FourHouse;
		break;
	case 5:
		ToPay = PayPrice.Hotel;
		break;
	default:
		ToPay = PayPrice.Initial;
	}
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(ToPay));
}

void AMonopolyHouseProperty::BuyHouse()
{
	Houses++;
}

FString AMonopolyHouseProperty::UpgradePrice()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(BuyPrice.House));
}

FString AMonopolyHouseProperty::PriceToBuy()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(BuyPrice.Initial));
}

FString AMonopolyHouseProperty::PriceToSell()
{
	return UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_IntToText(
		(BuyPrice.Initial + Houses * BuyPrice.House) / 2));
}

void AMonopolyHouseProperty::ResetInit()
{
	Super::ResetInit();
	Houses = 0;
}
