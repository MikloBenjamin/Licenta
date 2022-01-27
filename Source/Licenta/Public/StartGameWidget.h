// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "StartGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UComboBoxString* GetNrBots() { return NrBots; }
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Back;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* NrBots;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Init;
};
