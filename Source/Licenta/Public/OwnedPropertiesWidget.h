// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticipantPawn.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TileView.h"
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
	UImage* GetPropertyImage() const { return PropertyImage; }
	UTileView* GetProperties() { return Properties; }
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SellButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PropertyImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTileView* Properties;
};
