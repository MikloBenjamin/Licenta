// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions.generated.h"

UENUM(BlueprintType)
enum class EActions : uint8
{
	Default,
	Start,
	GoToJail,
	Property,
	RailroadN,
	RailroadS,
	RailroadE,
	RailroadW,
	Utility,
	Treasure,
	Mystery,
	Tax
};

UENUM(BlueprintType)
enum class EType : uint8
{
	Default,
	Property,
	Railroad,
	Utility,
	Card,
	Tax
};

UENUM(BlueprintType)
enum class ECardActions : uint8
{
	Get,
	Pay,
	PayToPlayers,
	GetFromPlayer,
	FreeFromJail,
	AdvanceTo,
	GoBack,
	Wasted,
	PayPerHouse = 40,
	PayPerHotel = 115
};

UENUM(BlueprintType)
enum class EPropGroups : uint8
{
	Brown,
	LightBlue,
	Pink,
	Orange,
	Red,
	Yellow,
	Green,
	DarkBlue
};

USTRUCT(BlueprintType)
struct FBuyPrice 
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	int Initial;
	
	UPROPERTY(BlueprintReadOnly)
	int House;
};

USTRUCT(BlueprintType)
struct FPayPrice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	int Initial;
	
	UPROPERTY(BlueprintReadOnly)
	int OneHouse;

	UPROPERTY(BlueprintReadOnly)
	int TwoHouse;

	UPROPERTY(BlueprintReadOnly)
	int ThreeHouse;
	
	UPROPERTY(BlueprintReadOnly)
	int FourHouse;
	
	UPROPERTY(BlueprintReadOnly)
	int Hotel;
};
