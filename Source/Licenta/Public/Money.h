// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Money.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UMoney final : public UUserDefinedStruct
{
	GENERATED_BODY()
	public:
		UMoney();
	
		UFUNCTION(BlueprintCallable, Category="Default")
		void Exchange(const int Amount);

		UFUNCTION(BlueprintCallable, Category="Default")
		int Total();

		UFUNCTION(BlueprintCallable, Category="Default")
		int GetTotal() const;
	
		UFUNCTION(BlueprintCallable, Category="Default")
		int Increase(int Amount);

		UFUNCTION(BlueprintCallable, Category="Default")
		int Calculate(const int Amount);
	
		UFUNCTION(BlueprintCallable, Category="Default")
		int CalcRest(int ToPay);
	
		UPROPERTY(BlueprintReadWrite, Category="Default")
		TMap<int, int> Money;
	
		UPROPERTY(BlueprintReadWrite, Category="Default")
		int TotalCash;
};
