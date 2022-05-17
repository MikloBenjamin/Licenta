// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TileView.h"
#include "Blueprint/UserWidget.h"
#include "BuyHouseWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UBuyHouseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UButton* GetBuyHouseButton() const { return BuyHouseButton; }
	UButton* GetBackButton() const { return BackButton; }
	UImage* GetPropertyImage() const { return PropertyImage; }
	UTileView* GetProperties() { return Properties_1; }
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BuyHouseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* PropertyImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTileView* Properties_1;
};
