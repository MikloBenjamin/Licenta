// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "InitialWidget.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UInitialWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Start;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Load;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Quit;
};
