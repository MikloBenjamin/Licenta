// Fill out your copyright notice in the Description page of Project Settings.


#include "MonopolyProperty.h"

AMonopolyProperty* AMonopolyProperty::Initialize(const FString Name, const EActions Action, FString AssetPath, AParticipantPawn* Player, bool IsOwnable)
{
	PropertyOwner = Player;
	PropertyName = Name;
	PropertyAction = Action;

	AssetPath = TEXT("/Game/Materials") + AssetPath;
	PropertyImage = LoadObject<UTexture2D>(nullptr, *AssetPath);
	// PrepareCppStructOps();
	CanBeOwned = IsOwnable;
	PropertyType = EType::Default;
	return this;
}

void AMonopolyProperty::ResetInit()
{
	PropertyOwner = nullptr;
}

