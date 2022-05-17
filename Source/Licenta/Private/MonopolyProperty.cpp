// Fill out your copyright notice in the Description page of Project Settings.


#include "MonopolyProperty.h"

AMonopolyProperty* AMonopolyProperty::Initialize(const int Position, const FString Name, const EActions Action, FString AssetPath, AParticipantPawn* Player, bool IsOwnable)
{
	PropertyPosition = Position;
	PropertyOwner = Player;
	PropertyName = Name;
	PropertyAction = Action;

	AssetPath = TEXT("/Game/Materials") + AssetPath;
	PropertyImage = NewObject<UImage>();
	PropertyTexture = LoadObject<UTexture2D>(nullptr, *AssetPath);
	CanBeOwned = IsOwnable;
	PropertyType = EType::Default;
	return this;
}

void AMonopolyProperty::ResetInit()
{
	PropertyOwner = nullptr;
}

