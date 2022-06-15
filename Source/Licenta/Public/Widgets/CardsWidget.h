// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "CardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UCardsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UTextBlock* GetCardInfo() const { return CardInfo; }
	UImage* GetInfoBackground() const { return InfoBackground; }
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CardInfo;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* InfoBackground;
};
