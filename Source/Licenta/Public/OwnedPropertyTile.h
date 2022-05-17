// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticipantPawn.h"
#include "MonopolyProperty.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "OwnedPropertyTile.generated.h"

/**
 * 
 */
UCLASS()
class LICENTA_API UOwnedPropertyTile : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Image;
	
	UOwnedPropertyTile* InitializeTile()
	{
		/*ImageButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());*/
		return this;
	}
};
