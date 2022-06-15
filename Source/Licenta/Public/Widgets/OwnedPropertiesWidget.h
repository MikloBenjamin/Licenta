// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TileView.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "OwnedPropertiesWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UOwnedPropertiesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UButton* GetSellButton() const { return SellButton; }
	UButton* GetBackButton() const { return BackButton; }
	UButton* GetDowngradeButton() const { return DowngradeButton; }
	UImage* GetPropertyImage() const { return PropertyImage; }
	UTileView* GetProperties() { return Properties; }
	UOverlay* GetHousesOverlay() { return HousesOverlay; }
	UTextBlock* GetHousesTextBlock() { return Houses; }
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SellButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PropertyImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTileView* Properties;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DowngradeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Houses;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* HousesOverlay;
};
