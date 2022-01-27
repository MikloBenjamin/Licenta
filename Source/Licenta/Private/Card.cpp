// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

// Sets default values
ACard::ACard(){}

ACard* ACard::Initialize(FString Name, ECardActions Action, int Get, int Pay, int Positions)
{
	Name_ = Name;
	Action_ = Action;
	Get_ = Get;
	Pay_ = Pay;
	Position_ = Positions;
	Keep_ = false;
	return this;
}


