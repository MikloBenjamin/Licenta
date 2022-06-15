// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Actions.h"
#include "Card.generated.h"

UCLASS()
class LICENTA_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	ACard();

	UFUNCTION(BlueprintCallable, Category="Default")
	ACard* Initialize(FString Name, ECardActions Action, int Get, int Pay, int Positions);
	
	UFUNCTION(BlueprintCallable, Category="Default")
	ACard* SetKeep(bool Keep)
	{
		Keep_ = Keep;
		return this;
	}
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	FString Name_;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	int Pay_;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	int Get_;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	int Position_;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	ECardActions Action_;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	bool Keep_;
};
