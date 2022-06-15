// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ParticipantPawn.h"
#include "Common/Actions.h"
#include "Components/Image.h"

#include "MonopolyProperty.generated.h"

/**
 * 
 */
UCLASS()
// class LICENTA_API UMonopolyProperty : public UUserDefinedStruct
class LICENTA_API AMonopolyProperty : public AActor
{
	GENERATED_BODY()
	protected:
		UPROPERTY(BlueprintReadWrite)
		AParticipantPawn* PropertyOwner = nullptr;

		UPROPERTY(BlueprintReadWrite)
		FString PropertyName;

		UPROPERTY(BlueprintReadWrite)
		EActions PropertyAction;

		UPROPERTY(BlueprintReadWrite)
		EType PropertyType;

		UPROPERTY(BlueprintReadWrite)
		UTexture2D* PropertyTexture;

		UPROPERTY(BlueprintReadWrite)
		UImage* PropertyImage;

		UPROPERTY(BlueprintReadWrite)
		bool CanBeOwned;

		UPROPERTY(BlueprintReadOnly)
		int PropertyPosition;
	public:
		UFUNCTION(BlueprintCallable, Category="Default")
		AMonopolyProperty* Initialize(const int Position, const FString Name, const EActions Action, FString AssetPath = "", AParticipantPawn* Player = nullptr, bool IsOwnable = false);
	
		UFUNCTION(BlueprintCallable, Category="Default")
		FString GetPropertyName() const { return PropertyName; }
	
		UFUNCTION(BlueprintCallable, Category="Default")
		EActions GetPropertyAction() const { return PropertyAction; }
	
		UFUNCTION(BlueprintCallable, Category="Default")
		EType GetPropertyType() const { return PropertyType; }

		UFUNCTION(BlueprintCallable, Category="Default")
		UTexture2D* GetPropertyTexture() const { return PropertyTexture; }

		UFUNCTION(BlueprintCallable, Category="Default")
		UImage* GetPropertyImage() const { return PropertyImage; }
	
		UFUNCTION(BlueprintCallable, Category = "Default")
		AParticipantPawn* GetPropertyOwner() const { return PropertyOwner; }

		UFUNCTION(BlueprintCallable, Category = "Default")
		int GetPropertyPosition() const { return PropertyPosition; }

		UFUNCTION(BlueprintCallable, Category = "Default")
		void SetPropertyOwner(AParticipantPawn* Participant) { PropertyOwner = Participant; }

		UFUNCTION(BlueprintCallable, Category = "Default")
		bool IsOwnable() const { return CanBeOwned; }

		UFUNCTION(BlueprintCallable, Category = "Default")
		bool IsPropertyType(EType Type) const { return PropertyType == Type; }


		// Virtual Methods
		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual FString PriceToPay(AParticipantPawn* PropertyOwnerParticipant) { return ""; };

		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual FString PriceToPayUtility(AParticipantPawn* PropertyOwnerParticipant, int DiceRolls) { return ""; };

		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual FString UpgradePrice() { return ""; };

		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual FString PriceToBuy() { return ""; };

		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual FString PriceToSell() { return ""; };

		UFUNCTION(BlueprintCallable, Category = "Default")
			virtual void ResetInit();
};
