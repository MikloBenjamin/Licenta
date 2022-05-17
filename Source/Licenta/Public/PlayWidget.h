// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "PlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UPlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHorizontalBox* GetPropertyInfo() const { return PropertyInfo; }
	UImage* GetPropertyImage() const { return PropertyImage; }
	UImage* GetPropertyOverlayImage() const { return PropertyInfoOverlay; }
	UTextBlock* GetPrice() const { return Price; }
	UTextBlock* GetPay() const { return Pay; }
	UTextBlock* GetOwner() const { return Owner; }
	UTextBlock* GetUpgrade() const { return Upgrade; }
	UTextBlock* GetC1() const { return C1; }
	UTextBlock* GetC2() const { return C2; }
	UTextBlock* GetC3() const { return C3; }
	UTextBlock* GetC4() const { return C4; }
	UTextBlock* GetC5() const { return C5; }
	UTextBlock* GetC6() const { return C6; }
	UTextBlock* GetC7() const { return C7; }
	UTextBlock* GetTotal() const { return Total; }
	UScaleBox* GetRTD() const { return RollTheDice; }
	UScaleBox* GetEndTurn() const { return EndTurn; }
	UButton* GetRtdButton() const { return RollTheDiceButton; }
	UButton* GetEndTurnButton() const { return EndTurnButton; }
	UButton* GetBuyButton() const { return BuyButton; }
	UButton* GetPayButton() const { return PayButton; }
	UButton* GetPropertiesButton() const { return PropertiesButton; }
	UButton* GetUpgradeButton() const { return UpgradeButton; }
	UScaleBox* GetBuyScaleBox() const { return BuyScaleBox; }
	UScaleBox* GetPropertiesScaleBox() const { return PropertiesScaleBox; }
	UScaleBox* GetPayScaleBox() const { return PayScaleBox; }
	UScaleBox* GetUpgradeScaleBox() const { return UpgradeScaleBox; }

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PropertyImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PropertyInfoOverlay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* PropertyInfo;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Price;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Pay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Owner;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Upgrade;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C5;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C6;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* C7;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Total;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* RollTheDice;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* EndTurn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RollTheDiceButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* EndTurnButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BuyButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PropertiesButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* UpgradeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* BuyScaleBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* PropertiesScaleBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* PayScaleBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScaleBox* UpgradeScaleBox;
};
