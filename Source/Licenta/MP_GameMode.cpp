// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_GameMode.h"

#include "AIPawn.h"
#include "PlayerPawn.h"
#include "Public/OwnedPropertyTile.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Kismet/KismetStringLibrary.h"
#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include <Runtime/Engine/Classes/Kismet/KismetTextLibrary.h>

//DECLARE_DYNAMIC_DELEGATE_OneParam(CustomEventSelectProperty, class AMonopolyProperty*, MonopolyProp)

void AMP_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMP_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMP_GameMode::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMP_GameMode::Initialize()
{
	FFileHelper::SaveStringToFile(FString("Initializing game\n"), *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
	PlayerTurn = 0;
	LastDiceRolled = 0;
	int pos = 0;

	MonopolyProperties = {
		NewObject<AMonopolyProperty>(GetTransientPackage(), TEXT("START"))->Initialize(pos++, "START", EActions::Start, "/Start"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("B1"))->Initialize(pos++, "Mediterranean Avenue", EActions::Property, "/BrownMediterranean", nullptr,
			{60, 50},
			{2, 10, 30, 90, 160, 250}),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chest1"))->Initialize(pos++, "Community Chest", EActions::Treasure, "/CommunityChest"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("B2"))->Initialize(pos++, "Baltic Avenue", EActions::Property, "/BrownBaltic", nullptr,
			{60, 50},
			{4, 20, 60, 180, 320, 450}),
		NewObject<ATax>(GetTransientPackage(), TEXT("TAX1"))->Initialize(pos++, "Income Tax", EActions::Tax, "/IncomeTax"),
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRS"))->Initialize(pos++, "Railroad South", EActions::Railroad, "/RailroadReading"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("LB1"))->Initialize(pos++, "Oriental Avenue", EActions::Property, "/LightBlueOriental", nullptr,
			{100, 50},
			{6, 30, 90, 270, 400, 550}, EPropGroups::LightBlue),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chance1"))->Initialize(pos++, "Chance", EActions::Mystery, "/Chance"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("LB2"))->Initialize(pos++, "Vermont Avenue", EActions::Property, "/LightBlueVermont", nullptr,
			{100, 50},
			{6, 30, 90, 270, 400, 550}, EPropGroups::LightBlue),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("LB3"))->Initialize(pos++, "Connecticut Avenue", EActions::Property, "/LightBlueConnecticut", nullptr,
			{120, 50},
			{8, 40, 100, 300, 450, 600}, EPropGroups::LightBlue),
		NewObject<AMonopolyProperty>(GetTransientPackage(), TEXT("JailVisit"))->Initialize(pos++, "Jail", EActions::Default, "/Jail"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("P1"))->Initialize(pos++, "St.Charles Place", EActions::Property, "/PinkCharles", nullptr,
			{140, 100},
			{10, 50, 150, 450, 625, 750}, EPropGroups::Pink),
		NewObject<AElectricAndWaterWorks>(GetTransientPackage(), TEXT("Electric1"))->Initialize(pos++, "Electric Company", EActions::Utility, "/ElectricCompany"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("P2"))->Initialize(pos++, "States Avenue", EActions::Property, "/PinkStates", nullptr,
			{140, 100},
			{10, 50, 150, 450, 625, 750}, EPropGroups::Pink),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("P3"))->Initialize(pos++, "Virginia Avenue", EActions::Property, "/PinkVirginia", nullptr,
			{160, 100},
			{12, 60, 180, 500, 700, 900}, EPropGroups::Pink),
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRW"))->Initialize(pos++, "Railroad West", EActions::Railroad, "/RailroadPennsylvania"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("O1"))->Initialize(pos++, "St.James Place", EActions::Property, "/OrangeJames", nullptr,
			{180, 100},
			{14, 70, 200, 550, 750, 950}, EPropGroups::Orange),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chest2"))->Initialize(pos++, "Community Chest", EActions::Treasure, "/CommunityChest"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("O2"))->Initialize(pos++, "Tennessee Avenue", EActions::Property, "/OrangeTennesse", nullptr,
			{180, 100},
			{14, 70, 200, 550, 750, 950}, EPropGroups::Orange),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("O3"))->Initialize(pos++, "New York Avenue", EActions::Property, "/OrangeNewYork", nullptr,
			{200, 100},
			{16, 80, 220, 600, 800, 1000}, EPropGroups::Orange),
		NewObject<AMonopolyProperty>(GetTransientPackage(), TEXT("Parking"))->Initialize(pos++, "Free Parking", EActions::Default, "/FreeParking"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("R1"))->Initialize(pos++, "Kentucky Avenue", EActions::Property, "/RedKentucky", nullptr,
			{220, 150},
			{18, 90, 250, 700, 875, 1050}, EPropGroups::Red),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chance2"))->Initialize(pos++, "Chance", EActions::Mystery, "/Chance"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("R2"))->Initialize(pos++, "Indiana Avenue", EActions::Property, "/RedIndiana", nullptr,
			{220, 150},
			{18, 90, 250, 700, 875, 1050}, EPropGroups::Red),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("R3"))->Initialize(pos++, "Illinois Avenue", EActions::Property, "/RedIllinois", nullptr,
			{240, 150},
			{20, 100, 300, 750, 925, 1100}, EPropGroups::Red),
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRN"))->Initialize(pos++, "Railroad North", EActions::Railroad, "/RailroadBO"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("Y1"))->Initialize(pos++, "Atlantic Avenue", EActions::Property, "/YellowAtlantic", nullptr,
			{260, 150},
			{22, 110, 330, 800, 975, 1150}, EPropGroups::Yellow),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("Y2"))->Initialize(pos++, "Ventnor Avenue", EActions::Property, "/YellowVentnor", nullptr,
			{260, 150},
			{22, 110, 330, 800, 975, 1150}, EPropGroups::Yellow),
		NewObject<AElectricAndWaterWorks>(GetTransientPackage(), TEXT("Electric2"))->Initialize(pos++, "Water Works", EActions::Utility, "/WaterWorks"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("Y3"))->Initialize(pos++, "Marvin Gardens", EActions::Property, "/YellowMarvin", nullptr,
			{280, 150},
			{24, 120, 360, 850, 1025, 1200}, EPropGroups::Yellow),
		NewObject<AMonopolyProperty>(GetTransientPackage(), TEXT("Jail"))->Initialize(pos++, "Go to Jail", EActions::GoToJail, "/GoToJail"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("G1"))->Initialize(pos++, "Pacific Avenue", EActions::Property, "/GreenPacific", nullptr,
			{300, 200},
			{26, 130, 390, 900, 1100, 1275}, EPropGroups::Green),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("G2"))->Initialize(pos++, "North Carolina Avenue", EActions::Property, "/GreenCarolina", nullptr,
			{300, 200},
			{26, 130, 390, 900, 1100, 1275}, EPropGroups::Green),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chest3"))->Initialize(pos++, "Community Chest", EActions::Treasure, "/CommunityChest"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("G3"))->Initialize(pos++, "Pennsylvania Avenue", EActions::Property, "/GreenPensylvania", nullptr,
			{320, 200},
			{28, 150, 450, 1000, 1200, 1400}, EPropGroups::Green),
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRE"))->Initialize(pos++, "Railroad East", EActions::Railroad, "/RailroadShortLine"),
		NewObject<ASecretCard>(GetTransientPackage(), TEXT("Chance3"))->Initialize(pos++, "Chance", EActions::Mystery, "/Chance"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("DB1"))->Initialize(pos++, "Park Palace", EActions::Property, "/DarkBluePark", nullptr,
			{350, 200},
			{35, 175, 500, 1100, 1300, 1500}, EPropGroups::DarkBlue),
		NewObject<ATax>(GetTransientPackage(), TEXT("TAX2"))->Initialize(pos++, "Luxury Tax", EActions::Tax, "/LuxuryTax"),
		NewObject<AMonopolyHouseProperty>(GetTransientPackage(), TEXT("DB2"))->Initialize(pos++, "Board Walk", EActions::Property, "/DarkBlueBoardwalk", nullptr,
			{400, 200},
			{50, 200, 600, 1400, 1700, 2000}, EPropGroups::DarkBlue)
	};

	ChanceCards = {
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToBoardwalk"))->Initialize("Advance to Board Walk", ECardActions::AdvanceTo, 0, 0, 39),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToGo"))->Initialize("Advance to GO(Collect $20)", ECardActions::AdvanceTo, 20, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToIllinois"))->Initialize("Advance to Illinois", ECardActions::AdvanceTo, 0, 0, 24),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToCharles"))->Initialize("Advance to St.Charles Place", ECardActions::AdvanceTo, 0, 0, 11),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToRailroad"))->Initialize("Advance to nearest Railroad", ECardActions::AdvanceTo, 0, 0, 5),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToRailroad2"))->Initialize("Advance to nearest Railroad", ECardActions::AdvanceTo, 0, 0, 5),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToUtility"))->Initialize("Advance to nearest Utility", ECardActions::AdvanceTo, 0, 0, 12),
		NewObject<ACard>(GetTransientPackage(), TEXT("Get50"))->Initialize("Bank pays you dividend of $50", ECardActions::Get, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("FreeFromJail"))->Initialize("Get Out of Jail Free", ECardActions::FreeFromJail, 0, 0, 0)->SetKeep(true),
		NewObject<ACard>(GetTransientPackage(), TEXT("GoBack"))->Initialize("Go Back 3 Spaces", ECardActions::GoBack, 0, 0, -3),
		NewObject<ACard>(GetTransientPackage(), TEXT("GoToJail"))->Initialize("Wasted! Go to Jail!", ECardActions::Wasted, 0, 0, 10),
		NewObject<ACard>(GetTransientPackage(), TEXT("PayForHouseAndHotels"))->Initialize("Repairs on your property, pay $25 for each house and $100 for each hotel", ECardActions::PayPerHouse, 0, 40, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("Pay15"))->Initialize("Speeding fine $50!", ECardActions::Pay, 0, 50, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToRailroadSouth"))->Initialize("Advance to Railroad South", ECardActions::AdvanceTo, 0, 0, 5),
		NewObject<ACard>(GetTransientPackage(), TEXT("PayToPlayers50"))->Initialize("You have been elected Chairman of the Board. Pay each player $50", ECardActions::PayToPlayers, 0, 50, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("Get150"))->Initialize("Your building loan matures. Collect $40", ECardActions::Get, 40, 0, 0)
	};

	ChestCards = {
		NewObject<ACard>(GetTransientPackage(), TEXT("AdvToGo2"))->Initialize("Advance to GO(Collect $20)", ECardActions::AdvanceTo, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("BankError"))->Initialize("Bank error in your favor! Collect $30", ECardActions::Get, 30, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("DoctorFee"))->Initialize("Doctor's fee. Pay $50", ECardActions::Pay, 0, 50, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("StockSale"))->Initialize("From sale of stock you get $20", ECardActions::Get, 20, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("FreeFromJail2"))->Initialize("Get Out of Jail for Free", ECardActions::FreeFromJail, 0, 0, 0)->SetKeep(true),
		NewObject<ACard>(GetTransientPackage(), TEXT("HolidayFunds"))->Initialize("Holiday Fund Matures. Receive $10", ECardActions::Get, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("IncomeTaxRefunds"))->Initialize("Income tax refunds. Get $20", ECardActions::Get, 20, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("Birthday"))->Initialize("It's your birthday! Get $10 from every player", ECardActions::GetFromPlayer, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("LifeInsuranceMatures"))->Initialize("Life insurance matures! Collect $10", ECardActions::Get, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("HospitalFees"))->Initialize("Pay hospital fees $100", ECardActions::Pay, 0, 100, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("SchoolFees"))->Initialize("Pay school fees $50", ECardActions::Pay, 0, 50, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("ConsultancyFee"))->Initialize("Receive $25 consultancy fee.", ECardActions::Get, 25, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("StreetRepair"))->Initialize("You are assessed for street repair. $40 per house. $115 per hotel", ECardActions::PayPerHouse, 0, 40, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("BeautyContestWin"))->Initialize("You have won second prize in a beauty contest. Collect $10", ECardActions::Get, 10, 0, 0),
		NewObject<ACard>(GetTransientPackage(), TEXT("Inheritance"))->Initialize("You inherit $100", ECardActions::Get, 10, 0, 0)
	};
	GenerateHouses();
	PlayMenu->GetCardInfoOverlay()->SetVisibility(ESlateVisibility::Collapsed);
	PlayMenu->GetMediaOverlay()->SetVisibility(ESlateVisibility::Collapsed);
}

void AMP_GameMode::ClearRoundTimer()
{
	if (GetWorldTimerManager().IsTimerActive(RoundTimer))
	{
		GetWorldTimerManager().ClearTimer(RoundTimer);
	}
}

void AMP_GameMode::SetRoundTimer()
{
	ClearRoundTimer();
	GetWorldTimerManager().SetTimer(RoundTimer, FTimerDelegate::CreateLambda([=]() {
		NextPlayer();
	}), 120, false);
}

void AMP_GameMode::ClearDiceRollTimer()
{
	if (GetWorldTimerManager().IsTimerActive(DiceRollTimer))
	{
		GetWorldTimerManager().ClearTimer(DiceRollTimer);
	}
}

void AMP_GameMode::SetDiceRollTimer()
{
	ClearDiceRollTimer();
	GetWorldTimerManager().SetTimer(DiceRollTimer, FTimerDelegate::CreateLambda([=]() {
		SetRollDiceAnimationTimer();
	}), 20, false);
}

void AMP_GameMode::ClearRollDiceAnimationTimer()
{
	if (GetWorldTimerManager().IsTimerActive(RollDiceAnimationTimer))
	{
		GetWorldTimerManager().ClearTimer(RollDiceAnimationTimer);
	}
}

void AMP_GameMode::SetRollDiceAnimationTimer()
{
	ClearDiceRollTimer();
	ClearRollDiceAnimationTimer();
	PlayMenu->GetMediaOverlay()->SetVisibility(ESlateVisibility::Visible);
	PlayMenu->GetDiceRollMediaPlayer()->OpenSource(PlayMenu->GetDiceRollSource());
	PlayMenu->GetButtons()->SetVisibility(ESlateVisibility::Hidden);
	PlayDiceRollSound();
	GetWorldTimerManager().SetTimer(RollDiceAnimationTimer, FTimerDelegate::CreateLambda([=]() {
		PlayMenu->GetMediaOverlay()->SetVisibility(ESlateVisibility::Collapsed);
		ExecutePlayerTurn();
		PlayMenu->GetButtons()->SetVisibility(ESlateVisibility::Visible);
		SetRoundTimer();
	}), 3.1, false);
}

void AMP_GameMode::ClearUseCardTimer()
{
	if (GetWorldTimerManager().IsTimerActive(UseCardTimer))
	{
		GetWorldTimerManager().ClearTimer(UseCardTimer);
	}
}

void AMP_GameMode::SetUseCardTimer()
{
	ClearUseCardTimer();
	PlayMenu->GetCardInfoOverlay()->SetVisibility(ESlateVisibility::Visible);
	GetWorldTimerManager().SetTimer(UseCardTimer, FTimerDelegate::CreateLambda([=]() {
		PlayMenu->GetCardInfoOverlay()->SetVisibility(ESlateVisibility::Collapsed);
	}), 10, false);
}

void AMP_GameMode::ClearSellForRestTimer()
{
	if (GetWorldTimerManager().IsTimerActive(SellForRestTimer))
	{
		GetWorldTimerManager().ClearTimer(SellForRestTimer);
	}
}

void AMP_GameMode::SetSellRestTimer()
{
	ClearSellForRestTimer();
	GetWorldTimerManager().SetTimer(SellForRestTimer, FTimerDelegate::CreateLambda([=]() {
		 ContinuePay();
	}), 180, false);
}

void AMP_GameMode::PayRest(AParticipantPawn* Player, int Rest, AParticipantPawn* Receiver)
{
	bool Continue = true;
	TArray<int> UtilitiesAndRailroads = { 12, 28, 5, 15, 25, 35 };

	TArray<TArray<int>> PropertyPositionByGroups = {
		{1, 3},
		{6, 8, 9},
		{11, 13, 14},
		{16, 18, 19},
		{21, 23, 24},
		{26, 27, 29},
		{31, 32, 34},
		{37, 39}
	};

	Log(FString("Selling properties\n"));
	for (TArray<int> groups : PropertyPositionByGroups)
	{
		bool SamePropOwner = true;
		bool NoHousesOwned = true;
		bool AnyPropertyOwned = false;
		for (int PropertyPosition : groups)
		{
			AMonopolyHouseProperty* Property = Cast<AMonopolyHouseProperty>(MonopolyProperties[PropertyPosition]);
			if (Property->GetHouses() > 0) NoHousesOwned = false;
			if (Property->GetPropertyOwner() != Player) SamePropOwner = false;
			else AnyPropertyOwned = true;
		}

		if (AnyPropertyOwned && (!SamePropOwner || NoHousesOwned || (SamePropOwner && NoHousesOwned)))
			for (int PropertyPosition : groups)
				if (MonopolyProperties[PropertyPosition]->GetPropertyOwner() == Player)
				{
					SellProperty(PropertyPosition, Player);
					Player->Pay(Player->Rest, Receiver);
					Log(FString::Format(TEXT("Player {0} sold {1} --- Rest = {2}\n"), { Player->GetParticipantName(), MonopolyProperties[PropertyPosition]->GetPropertyName(), Rest }));
				}
	}

	if (Rest > 0)
	{
		Log(FString("Selling railroads and utilites\n"));
		for (int PropertyPosition : UtilitiesAndRailroads)
		{
			if (MonopolyProperties[PropertyPosition]->GetPropertyOwner() == Player)
			{
				SellProperty(PropertyPosition, Player);
				Player->Pay(Player->Rest, Receiver);
				Log(FString::Format(TEXT("Player {0} sold {1} --- Rest = {2}\n"), { Player->GetParticipantName(), MonopolyProperties[PropertyPosition]->GetPropertyName(), Rest }));
			}
		}
	}

	if (Player->Rest > 0)
	{
		Log(FString("Selling Houses\n"));
		for (TArray<int> groups : PropertyPositionByGroups)
		{
			bool SamePropOwner = true;

			for (int PropertyPosition : groups)
			{
				if (DegradePossible(MonopolyProperties[PropertyPosition], Player))
				{
					SellHouse(MonopolyProperties[PropertyPosition], Player);
					Player->Pay(Player->Rest, Receiver);
					Log(FString::Format(TEXT("Player {0} sold house on {1} --- Rest = {2}\n"), { Player->GetParticipantName(), MonopolyProperties[PropertyPosition]->GetPropertyName(), Rest }));
				}
				if (Player->Rest <= 0) break;
			}
			if (Player->Rest <= 0) break;
		}
	}
	Log(FString::Format(TEXT("Leaving PayRest --- Rest left: {0}\n"), {Rest}));
}

void AMP_GameMode::HandleRest(AParticipantPawn* Player, int Rest, AParticipantPawn* Receiver)
{
	FString ReceiverName = Receiver ? Receiver->GetParticipantName() : "BANK";
	Log(FString::Format(TEXT("Player: {0} ... OWES ... {1} ... TO ... {2}\n"), {Player->GetParticipantName(), Rest, ReceiverName }));
	if (!Player->IsBot() && Rest > 0)
	{
		HandleMoneyInfo(Player->GetMoney());
		PlayMenu->SetVisibility(ESlateVisibility::Collapsed);
		GenerateTilesForRestWidget();
		Player->Rest = Rest;
		PayRestMenu->RestPay = Rest;
		SetSellRestTimer();
		PayRestMenu->GetSellButton()->SetVisibility(ESlateVisibility::Collapsed);
		PayRestMenu->GetContinueButton()->SetVisibility(ESlateVisibility::Collapsed);
		PayRestMenu->GetDowngradeButton()->SetVisibility(ESlateVisibility::Collapsed);
		PayRestMenu->GetRestTextBlock()->SetText(UKismetTextLibrary::Conv_IntToText(Rest));
		BindPayRestButtons();
	}
	else if (Rest > 0)
	{
		PayRest(Player, Rest, Receiver);
		if (Player->Rest > 0)
		{
			Log(FString::Format(TEXT("Player: {0} LOST, removing from list\n"), {Player->GetParticipantName()}));
			Players.Remove(Player);
			PlayerTurn--;
			if (Players.Num() > 1)
				NextPlayer();
			else {
				GameOverMenu->Show(FText::FromString("Congratulations! You Win!"));
			}
		}
	}
}

void AMP_GameMode::RecalculateRestInformation()
{
	PayRestMenu->SetVisibility(ESlateVisibility::Collapsed);
	PayRestMenu->SetVisibility(ESlateVisibility::Visible);
	AParticipantPawn* Player = GetParticipant();
	int Total = Player->GetMoney()->Total();
	if (Total >= Player->Rest)
	{
		PayRestMenu->GetRestOverlay()->SetVisibility(ESlateVisibility::Collapsed);
		PayRestMenu->GetContinueButton()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PayRestMenu->RestPay = Player->Rest;
		PayRestMenu->GetRestTextBlock()->SetText(UKismetTextLibrary::Conv_IntToText(Player->Rest));
	}
}

void AMP_GameMode::ContinuePay()
{
	AParticipantPawn* Player = GetParticipant();
	PayRestMenu->SetVisibility(ESlateVisibility::Collapsed);
	if (Player->GetMoney()->Total() >= Player->Rest)
	{
		Player->Pay(Player->Rest, MonopolyProperties[Player->GetPlayerPosition()]->GetPropertyOwner());
		PlayMenu->SetVisibility(ESlateVisibility::Collapsed);
		HandlePlayMenu(true, MonopolyProperties[Player->GetPlayerPosition()]);
	}
	else
	{
		/// Eliminate from list, destroy, remove from owned properties, houses
		Players.Empty();
		MonopolyProperties.Empty();
		ChanceCards.Empty();
		ChestCards.Empty();
		/// show Game Over with lose info
		GameOverMenu->Show(FText::FromString("You Lost!"));
	}
}

void AMP_GameMode::StartGame(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials)
{
	Log("Starting game\n");
	GeneratePlayers(PlayerController, StaticMeshList, Materials);
	const int32 NumShuffles = Players.Num() - 1;
	for (int32 i = 0; i < NumShuffles; ++i)
	{
		int32 SwapIdx = FMath::RandRange(i, NumShuffles);
		Players.Swap(i, SwapIdx);
	}
	
	if (Players[0]->IsBot()) NextPlayer();
	HandlePlayMenu(true, MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()]);
	HandlePropertyInfo(MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()], Players[PlayerTurn]);
	HandleMoneyInfo(Players[PlayerTurn]->Money);
	SetDiceRollTimer();
}

void AMP_GameMode::GenerateHouses()
{
	auto generateHouses = [&](FVector location, FRotator rotation, int propPosition, EPropGroups group, FVector moveBy) {
		FHouses houses;
		houses.group = group;
		for (int houseNr = 0; houseNr < 3; houseNr++)
		{
			houses.houses.Add(GetWorld()->SpawnActor<APropertyHouse>(location, rotation));
			location += moveBy;
		}
		Houses.Add(propPosition, houses);
	};

	// FRotator(Y, Z, X)
	FRotator rotation = { 0, 90, 0 };
	FVector moveBy = { -115, 0, 0 };
	generateHouses({ -65, -155, 1200 }, rotation, 1, EPropGroups::Brown, moveBy); // Brown 1 houses
	generateHouses({ -860, -155, 1200 }, rotation, 3, EPropGroups::Brown, moveBy); // Brown 2 Houses

	generateHouses({ -2060, -155, 1200 }, rotation, 6, EPropGroups::LightBlue, moveBy); // LightBlue 1 houses
	generateHouses({ -2860, -155, 1200 }, rotation, 8, EPropGroups::LightBlue, moveBy); // LightBlue 2 houses
	generateHouses({ -3260, -155, 1200 }, rotation, 9, EPropGroups::LightBlue, moveBy); // LightBlue 3 houses

	rotation = { 0, 180, 0 };
	moveBy = { 0, -115, 0 };
	generateHouses({ -3625, -280, 1200 }, rotation, 11, EPropGroups::Pink, moveBy); // Pink 1 houses
	generateHouses({ -3625, -1080, 1200 }, rotation, 13, EPropGroups::Pink, moveBy); // Pink 2 houses
	generateHouses({ -3625, -1480, 1200 }, rotation, 14, EPropGroups::Pink, moveBy); // Pink 3 houses

	generateHouses({ -3625, -2280, 1200 }, rotation, 16, EPropGroups::Orange, moveBy); // Orange 1 houses
	generateHouses({ -3625, -3080, 1200 }, rotation, 18, EPropGroups::Orange, moveBy); // Orange 2 houses
	generateHouses({ -3625, -3480, 1200 }, rotation, 19, EPropGroups::Orange, moveBy); // Orange 3 houses

	rotation = { 0, 270, 0 };
	moveBy = { 115, 0, 0 };
	generateHouses({ -3505, -3845, 1200 }, rotation, 21, EPropGroups::Red, moveBy); // Red 1 houses
	generateHouses({ -2705, -3845, 1200 }, rotation, 23, EPropGroups::Red, moveBy); // Red 2 houses
	generateHouses({ -2305, -3845, 1200 }, rotation, 24, EPropGroups::Red, moveBy); // Red 3 houses

	generateHouses({ -1505, -3845, 1200 }, rotation, 26, EPropGroups::Yellow, moveBy); // Yellow 1 houses
	generateHouses({ -1105, -3845, 1200 }, rotation, 27, EPropGroups::Yellow, moveBy); // Yellow 2 houses
	generateHouses({ -305, -3845, 1200 }, rotation, 29, EPropGroups::Yellow, moveBy); // Yellow 3 houses

	rotation = { 0, 0, 0 };
	moveBy = { 0, 115, 0 };
	generateHouses({ 65, -3725, 1200 }, rotation, 31, EPropGroups::Green, moveBy); // Green 1 houses
	generateHouses({ 65, -3325, 1200 }, rotation, 32, EPropGroups::Green, moveBy); // Green 2 houses
	generateHouses({ 65, -2525, 1200 }, rotation, 34, EPropGroups::Green, moveBy); // Green 3 houses

	generateHouses({ 65, -1325, 1200 }, rotation, 37, EPropGroups::DarkBlue, moveBy); // DarkBlue 1 houses
	generateHouses({ 65, -525, 1200 }, rotation, 39, EPropGroups::DarkBlue, moveBy); // DarkBlue 2 houses
}

void AMP_GameMode::GeneratePlayers(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials)
{
	const int NumberOfBots = UKismetStringLibrary::Conv_StringToInt(StartMenu->GetNrBots()->GetSelectedOption());

	auto CreateBot = [&](FVector Loc, FRotator Rot, FActorSpawnParameters SpawnInfo, FString Name, UStaticMesh* StaticMesh, UMaterial* Material) {
		AParticipantPawn* Bot = GetWorld()->SpawnActor<AAIPawn>(Loc, Rot, SpawnInfo);
		Bot->Initialize(Name, StaticMesh, Material);
		return Bot;
	};
	FVector Location(160.0f, -50.0f, 1150.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AParticipantPawn* Player = GetWorld()->SpawnActor<APlayerPawn>(Location, Rotation, SpawnInfo);
	PlayerController->Possess(Player);
	Player->Initialize("Player 1", StaticMeshList[0], Materials[0]);
	Players.Add(Player);
	UE_LOG(LogTemp, Log, TEXT("SetupGame -> Player Added"));

	Players.Add(CreateBot({ 160.0f, 60.0f, 1150.0f }, Rotation, SpawnInfo, "Bot 1", StaticMeshList[1], Materials[1]));
	UE_LOG(LogTemp, Log, TEXT("SetupGame -> Bot 1 Added"));

	if (NumberOfBots > 1)
	{
		Players.Add(CreateBot({ 270.0f, -50.0f, 1150.0f }, Rotation, SpawnInfo, "Bot 2", StaticMeshList[2], Materials[2]));
		UE_LOG(LogTemp, Log, TEXT("SetupGame -> Bot 2 Added"));
	}

	if (NumberOfBots > 2)
	{
		Players.Add(CreateBot({ 270.0f, 60.0f, 1150.0f }, Rotation, SpawnInfo, "Bot 3", StaticMeshList[3], Materials[3]));
		UE_LOG(LogTemp, Log, TEXT("SetupGame -> Bot 3 Added"));
	}
	CHEAT();
}

void AMP_GameMode::Log(FString log)
{
	FFileHelper::SaveStringToFile(log, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

void AMP_GameMode::NextPlayer()
{
	NextPlayerTurn();
	AParticipantPawn* Player = GetParticipant();
	if (Player->IsBot())
	{
		SetRoundTimer();
		PlayMenu->SetVisibility(ESlateVisibility::Collapsed);

		ExecuteBotTurn();
		NextPlayer();
	}
	else
	{
		ClearRoundTimer();
		SetDiceRollTimer();
		HandlePlayMenu(true, MonopolyProperties[Player->GetPlayerPosition()]);
		HandlePropertyInfo(MonopolyProperties[Player->GetPlayerPosition()], Player);
		HandleMoneyInfo(Player->GetMoney());
	}
}

void AMP_GameMode::NextPlayerTurn()
{
	PlayerTurn = ((PlayerTurn == (Players.Num() - 1)) ? 0 : PlayerTurn + 1);
	if (PlayerTurn == 0)
	{
		GetParticipant()->SetRolled(false);
	}
}

void AMP_GameMode::ExecuteBotTurn()
{
	AParticipantPawn* Player = Players[PlayerTurn];
	if (Player->IsBot())
	{
		LastDiceRolled = Player->Play();
		Log(FString::Format(TEXT("Player {0} stepped on {1}\n"), { Player->GetParticipantName(), MonopolyProperties[Player->GetPlayerPosition()]->GetPropertyName() }));
		HandleProperty(MonopolyProperties[Player->GetPlayerPosition()], Player);
	}
}

AMonopolyProperty* AMP_GameMode::ExecutePlayerTurn()
{
	ClearDiceRollTimer();
	AParticipantPawn* Player = Players[PlayerTurn];

	LastDiceRolled = Player->Play();
	Player->SetRolled(true);
	Log(FString::Format(TEXT("Player {0} stepped on {1}\n"), { Player->GetParticipantName(), MonopolyProperties[Player->GetPlayerPosition()]->GetPropertyName() }));

	int Position = Player->GetPlayerPosition();
	HandleProperty(MonopolyProperties[Position]);
	Position = Player->GetPlayerPosition();
	HandlePlayMenu(false, MonopolyProperties[Position]);
	HandlePropertyInfo(MonopolyProperties[Position], Player);
	HandleMoneyInfo(Player->GetMoney());
	return GetProperty(Position);
}

void AMP_GameMode::HandleProperty(AMonopolyProperty* Property, AParticipantPawn* Player)
{
	if (!Player) Player = GetParticipant();
	EType prop_type = Property->GetPropertyType();
	EActions prop_action = Property->GetPropertyAction();

	int Rest;
	FString PriceToPayS;
	int PriceToPay;

	switch (prop_action)
	{
	case EActions::Mystery:
		if (!Player->IsBot())
		{
			SetUseCardTimer();
			PlayMenu->GetInfoBackground()->SetColorAndOpacity({1, 0.35, 0, 1});
		}
		UseCard(ChanceCards);
		break;
	case EActions::Treasure:
		if (!Player->IsBot())
		{
			SetUseCardTimer();
			PlayMenu->GetInfoBackground()->SetColorAndOpacity({ 1, 1, 0.15, 1 });
		}
		UseCard(ChestCards);
		break;
	case EActions::GoToJail:
		if (!IsValid(Player->Card))
		{
			Player->JailedFor = 3;
			Log(FString::Format(TEXT("Player {0} jailed, moving {1} positions\n"), { Player->GetParticipantName(), 20 }));
			Player->Move(20);
			Log(FString::Format(TEXT("Player {0} current position {1}\n"), { Player->GetParticipantName(), Player->GetPlayerPosition() }));
		}
		else
		{
			Log(FString("Player has card! BAD\n"));
			if (ChanceCards.Num() < 16)
			{
				ChanceCards.Add(Player->Card);
			}
			else if (ChestCards.Num() < 16)
			{
				ChestCards.Add(Player->Card);
			}
			Player->Card = nullptr;
		}
		break;
	case EActions::Tax:
		Log(FString::Format(TEXT("Player {0} landed on a TAX property\n"), {Player->GetParticipantName()}));
		if (Property->GetPropertyPosition() == 38)
		{
			// Luxury Tax
			Rest = Player->Pay(150);
			HandleRest(Player, Rest);
		}
		else
		{
			// Income Tax
			Rest = Player->Pay(FMath::Min(Player->GetMoney()->Total() / 10, 200));
			HandleRest(Player, Rest);
		}
		break;
	case EActions::Utility:
	case EActions::Railroad:
	case EActions::Property:
		if (Property->GetPropertyOwner() != nullptr)
		{
			if (Property->GetPropertyOwner() != Player)
			{
				/// Pay / Trade? / Sell Props / Lose
				PriceToPayS = Property->PriceToPay(Player);
				PriceToPay = FCString::Atoi(*PriceToPayS);
				Rest = Player->Pay(PriceToPay, Property->GetPropertyOwner());
				Log(FString::Format(TEXT("Player {0} paid {1} to {2}\n"), { Player->GetParticipantName(), PriceToPay - Rest, Property->GetPropertyOwner()->GetParticipantName() }));
				HandleRest(Player, Rest);
			}
			else
			{
				if (Player->IsBot())
				{
					HandleBotAI(Player, Property);
				}
			}
		}
		else
		{
			if (Player->IsBot())
			{
				/// BOT AI to Buy / Upgrade / Sell Other + Buy This
				HandleBotAI(Player, Property);
			}
		}

		break;
	default:
		break;
	}
}

void AMP_GameMode::UseCard(TArray<ACard*> &Cards)
{
	AParticipantPawn* Player = GetParticipant();
	ACard* card = Cards[0];

	PlayMenu->GetCardInfo()->SetText(UKismetTextLibrary::Conv_StringToText(card->Name_));

	Cards.RemoveAt(0);
	if (!card->Keep_)
		Cards.Add(card);
	else
	{
		if (IsValid(Player->Card))
		{
			Cards.Add(card);
		}
		else
		{
			Player->Card = card;
		}
		return;
	}

	int destination = 0;
	int Rest;
	switch (card->Action_)
	{
	case ECardActions::AdvanceTo:
		destination = card->Position_ - Player->GetPlayerPosition();
		if (destination < 0)
		{
			destination = 40 + destination;
		}
		Player->Move(destination);
		break;
	case ECardActions::Get:
		Player->Receive(card->Get_);
		break;
	case ECardActions::GetFromPlayer:
		for (AParticipantPawn* player : Players)
		{
			if (player != Player)
			{
				Player->Receive(card->Get_);
				Rest = player->Pay(card->Get_, Player);
				HandleRest(player, Rest, Player);
			}
		}
		break;
	case ECardActions::GoBack:
		Player->JailedFor = 3;
		Player->Move(37); // Move back 3 space
		Player->JailedFor = 0;
		break;
	case ECardActions::Pay:
		Rest = Player->Pay(card->Pay_);
		HandleRest(Player, Rest);
		break;
	case ECardActions::PayPerHotel:
		break;
	case ECardActions::PayPerHouse:
		break;
	case ECardActions::PayToPlayers:
		for (AParticipantPawn* player : Players)
		{
			if (player != Player)
			{
				Rest = Player->Pay(card->Pay_);
				HandleRest(Player, Rest);
			}
		}
		break;
	case ECardActions::Wasted:
		if (Player->Card)
		{
			Player->Card = nullptr;
		}
		else
		{
			Player->JailedFor = 3;
			int MoveBy = 10 - Player->GetPlayerPosition();
			MoveBy = (MoveBy < 0 ? 40 + MoveBy : MoveBy);
			Log(FString::Format(TEXT("Player {0} jailed, moving {1} positions\n"), { Player->GetParticipantName(), MoveBy }));
			Player->Move(MoveBy);
			Log(FString::Format(TEXT("Player {0} current position {1}\n"), { Player->GetParticipantName(), Player->GetPlayerPosition() }));
		}
		break;
	default:
		break;
	}
}

void AMP_GameMode::HandleShowStartMenu()
{
	InitialMenu->SetVisibility(ESlateVisibility::Collapsed);
	StartMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMP_GameMode::HandlePlayMenu(bool StartTurn, AMonopolyProperty* Property)
{
	if (IsValid(Property))
	{
		PlayMenu->GetPropertyImage()->SetBrushFromTexture(Property->GetPropertyTexture());
	}

	if (StartTurn)
	{
		PlayMenu->SetVisibility(ESlateVisibility::Visible);
		PlayMenu->GetRTD()->SetVisibility(ESlateVisibility::Visible);
		PlayMenu->GetEndTurn()->SetVisibility(ESlateVisibility::Collapsed);

		Property = MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()];
		if (IsValid(Property))
		{
			PlayMenu->GetPropertyImage()->SetBrushFromTexture(Property->GetPropertyTexture());
		}
	}
	else
	{
		PlayMenu->GetRTD()->SetVisibility(ESlateVisibility::Collapsed);
		PlayMenu->GetEndTurn()->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMP_GameMode::HandlePropertyInfo(AMonopolyProperty* Property, AParticipantPawn* Participant)
{
	PlayMenu->GetPropertyInfo()->SetVisibility(ESlateVisibility::Visible);
	if (IsValid(Property) && Property->IsOwnable())
	{
		PlayMenu->GetPropertyOverlayImage()->SetOpacity(1.0);

		switch (Property->GetPropertyType()) {
			case EType::Property:
			case EType::Railroad:
			case EType::Utility:
				HandleOwnedProperty(Property, Participant);
				break;
			default:
				break;
		}
	}
	else
	{
		PlayMenu->GetPropertyInfo()->SetVisibility(ESlateVisibility::Hidden);
		PlayMenu->GetPropertyOverlayImage()->SetOpacity(0.0);
		PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
		PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMP_GameMode::HandleOwnedProperty(AMonopolyProperty* Property, AParticipantPawn* Participant)
{
	CalculateCanBuySellHouseOrProperty();
	AParticipantPawn* PropertyOwner = Property->GetPropertyOwner();

	if (IsValid(PropertyOwner))
	{
		Log(FString::Format(TEXT("Property {0} owner: {1}\n"), { Property->GetPropertyName(), Property->GetPropertyOwner()->GetParticipantName() }));
		PlayMenu->GetOwner()->SetText(UKismetTextLibrary::Conv_StringToText(PropertyOwner->GetParticipantName()));
		if (PropertyOwner == Participant)
		{
			PlayMenu->GetUpgrade()->SetText(UKismetTextLibrary::Conv_StringToText(Property->UpgradePrice()));
			PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(""));
			PlayMenu->GetPrice()->SetText(UKismetTextLibrary::Conv_StringToText(""));
			PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			if (UpgradePossible(Property, Participant))
			{
				PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(Property->PriceToPay(Property->GetPropertyOwner())));
			if (Property->IsPropertyType(EType::Utility))
			{
				PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(Property->PriceToPayUtility(Property->GetPropertyOwner(), LastDiceRolled)));
			}
			PlayMenu->GetPrice()->SetText(UKismetTextLibrary::Conv_StringToText("OWNED"));
			PlayMenu->GetUpgrade()->SetText(UKismetTextLibrary::Conv_StringToText(""));
			PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		Log(FString::Format(TEXT("Property {0} has NO owner --- PLAYER: {1}\n"), { Property->GetPropertyName(), Participant->GetParticipantName()}));
		PlayMenu->GetOwner()->SetText(UKismetTextLibrary::Conv_StringToText(""));
		PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(""));
		PlayMenu->GetPrice()->SetText(UKismetTextLibrary::Conv_StringToText(Property->PriceToBuy()));
		PlayMenu->GetUpgrade()->SetText(UKismetTextLibrary::Conv_StringToText(Property->UpgradePrice()));
		// Show buy button here, hide pay button, hide sell button
		if (Participant->GetMoney()->Total() >= FCString::Atoi(*Property->PriceToSell()))
			PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Visible);
		PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMP_GameMode::HandleMoneyInfo(UMoney* PlayerMoney)
{
	TMap<int, int> Money = PlayerMoney->Money;
	int Total = PlayerMoney->Total();

	PlayMenu->GetC1()->SetText(UKismetTextLibrary::Conv_IntToText(Money[1]));
	PlayMenu->GetC2()->SetText(UKismetTextLibrary::Conv_IntToText(Money[5]));
	PlayMenu->GetC3()->SetText(UKismetTextLibrary::Conv_IntToText(Money[10]));
	PlayMenu->GetC4()->SetText(UKismetTextLibrary::Conv_IntToText(Money[20]));
	PlayMenu->GetC5()->SetText(UKismetTextLibrary::Conv_IntToText(Money[50]));
	PlayMenu->GetC6()->SetText(UKismetTextLibrary::Conv_IntToText(Money[100]));
	PlayMenu->GetC7()->SetText(UKismetTextLibrary::Conv_IntToText(Money[500]));
	PlayMenu->GetTotal()->SetText(UKismetTextLibrary::Conv_IntToText(Total));
}

void AMP_GameMode::HandleBackToInitialMenu()
{
	StartMenu->SetVisibility(ESlateVisibility::Collapsed);
	PlayMenu->SetVisibility(ESlateVisibility::Collapsed);
	InitialMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMP_GameMode::ShowPropertiesMenu()
{
	PlayMenu->SetIsEnabled(false);
	CalculateCanBuySellHouseOrProperty();
	OwnedPropertiesMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMP_GameMode::HidePropertiesMenu()
{
	OwnedPropertiesMenu->SetVisibility(ESlateVisibility::Collapsed);
	PlayMenu->SetIsEnabled(true);
	HandlePlayMenu(!GetParticipant()->GetRolled(), MonopolyProperties[GetParticipant()->GetPlayerPosition()]);
}

void AMP_GameMode::ShowSameGroupMenu()
{
	PlayMenu->SetIsEnabled(false);
	BuyHouseMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMP_GameMode::HideSameGroupMenu()
{
	BuyHouseMenu->SetVisibility(ESlateVisibility::Collapsed);
	PlayMenu->SetIsEnabled(true);
	HandlePlayMenu(!GetParticipant()->GetRolled(), MonopolyProperties[GetParticipant()->GetPlayerPosition()]);
}

void AMP_GameMode::BuyProperty(AMonopolyProperty* Property, AParticipantPawn* Player)
{
	if (!Player) Player = GetParticipant();
	if (!Property) Property = MonopolyProperties[Player->GetPlayerPosition()];

	Player->Pay(FCString::Atoi(*Property->PriceToBuy()));
	Log(FString::Format(TEXT("Player {0} bought {1}\n"), { Player->GetParticipantName(), Property->GetPropertyName() }));

	Property->SetPropertyOwner(Player);
	HandlePropertyInfo(Property, Player);
	HandleMoneyInfo(Player->GetMoney());
}

void AMP_GameMode::SellProperty(const int Position, AParticipantPawn *Player)
{
	if (!Player)
		Player = GetParticipant();
	AMonopolyProperty* Property = MonopolyProperties[Position];

	Log(FString::Format(TEXT("Propery price: {0} --- Player Money initial: {1}\n"), { Property->PriceToSell(), Player->GetMoney()->Total()}));
	Player->Receive(FCString::Atoi(*Property->PriceToSell()));
	Log(FString::Format(TEXT("Player Money After: {0}\n"), {Player->GetMoney()->Total()}));
	Property->ResetInit();
	if (!Player->IsBot())
	{
		HandlePropertyInfo(Property, Player);
		HandleMoneyInfo(Player->GetMoney());
	}
}

bool AMP_GameMode::UpgradePossible(AMonopolyProperty* Property, AParticipantPawn* Participant)
{
	AMonopolyHouseProperty* HouseProperty = Cast<AMonopolyHouseProperty>(Property);
	if (!HouseProperty)
	{
		return false;
	}

	EPropGroups group = HouseProperty->GetPropGroup();

	int count = 0, max_count = (group == EPropGroups::Brown || group == EPropGroups::DarkBlue ? 2 : 3);

	for (int i = 0; i < 40 && count < max_count; i++)
	{
		AMonopolyHouseProperty *prop = Cast<AMonopolyHouseProperty>(MonopolyProperties[i]);
		if (prop && prop->GetPropertyOwner() == Participant && prop->GetPropGroup() == group) count++;
	}

	return count == max_count;
}

bool AMP_GameMode::DegradePossible(AMonopolyProperty* Property, AParticipantPawn* Participant)
{
	AMonopolyHouseProperty* HouseProperty = Cast<AMonopolyHouseProperty>(Property);
	if (!HouseProperty)
	{
		return false;
	}

	return HouseProperty->GetHouses() > 0;
}

void AMP_GameMode::UpgradeProperty(AMonopolyProperty* Property, AParticipantPawn* Player)
{
	if (!Player) Player = GetParticipant();
	AMonopolyHouseProperty* HouseProperty = Cast<AMonopolyHouseProperty>(Property);
	FHouses houses = Houses[HouseProperty->GetPropertyPosition()];
	for (int i = 0; i < houses.houses.Num(); i++)
	{
		if (!houses.houses[i]->prop_owner)
		{
			houses.houses[i]->GetStaticMeshComponent()->SetMaterial(0, GetParticipant()->color);
			HouseProperty->BuyHouse();
			GetParticipant()->Pay(FCString::Atoi(*(HouseProperty->UpgradePrice())));
			houses.houses[i]->prop_owner = GetParticipant();
			break;
		}
	}
	
	if (Player->IsBot()) return;

	HandlePropertyInfo(Property, Player);
	HandleMoneyInfo(Player->GetMoney());
}

void AMP_GameMode::SellHouse(AMonopolyProperty* Property, AParticipantPawn* Player)
{
	if (!Player)
		Player = GetParticipant();
	AMonopolyHouseProperty* HouseProperty = Cast<AMonopolyHouseProperty>(Property);
	FHouses houses = Houses[HouseProperty->GetPropertyPosition()];
	for (int i = houses.houses.Num() - 1; i >= 0; i--)
	{
		if (houses.houses[i]->prop_owner)
		{
			houses.houses[i]->GetStaticMeshComponent()->SetMaterial(0, nullptr);
			HouseProperty->SellHouse();
			Player->Receive(FCString::Atoi(*(HouseProperty->UpgradePrice())));
			houses.houses[i]->prop_owner = nullptr;
			break;
		}
	}
	if (!Player->IsBot())
	{
		HandlePropertyInfo(Property, Player);
		HandleMoneyInfo(Player->GetMoney());
	}
}

int AMP_GameMode::Pay(const int Amount)
{
	return GetParticipant()->Pay(Amount);
}

AParticipantPawn* AMP_GameMode::GetParticipant()
{
	return Players[PlayerTurn];
}

AMonopolyProperty* AMP_GameMode::GetProperty(const int Position)
{
	return MonopolyProperties[Position];
}

void AMP_GameMode::CHEAT()
{
	MonopolyProperties[1]->SetPropertyOwner(GetParticipant());
	MonopolyProperties[3]->SetPropertyOwner(GetParticipant());

	Players[0]->Pay(900);
	for (int i = 1; i < Players.Num(); i++)
	{
		Players[i]->Pay(500);
	}

	/*APlayerPawn* Player = Cast<APlayerPawn>(GetParticipant());
	Player->CheatMove();*/
}

void AMP_GameMode::CalculateCanBuySellHouseOrProperty()
{
	AParticipantPawn* Participant = GetParticipant();
	int max_houses = 0;
	for (AMonopolyProperty* MProperty : MonopolyProperties)
	{
		AMonopolyHouseProperty* MHouseProperty = Cast<AMonopolyHouseProperty>(MProperty);
		if (!MHouseProperty) continue;

		EPropGroups group = MHouseProperty->GetPropGroup();

		int count = 0, max_count = (group == EPropGroups::Brown || group == EPropGroups::DarkBlue ? 2 : 3);
		max_houses = MHouseProperty->GetHouses();
		for (int i = 0; i < 40 && count < max_count; i++)
		{
			AMonopolyHouseProperty* prop = Cast<AMonopolyHouseProperty>(MonopolyProperties[i]);
			if (prop && prop->GetPropertyOwner() == Participant && prop->GetPropGroup() == group)
			{
				count++;
				if (prop != MHouseProperty)
				{
					max_houses = prop->GetHouses() > max_houses ? prop->GetHouses() : max_houses;
				}
			}
		}


		MHouseProperty->CanBuyHouse = UpgradePossible(MHouseProperty, Participant);
		MHouseProperty->CanSellHouse = DegradePossible(MHouseProperty, Participant);

		if (count < max_count || max_houses == 0)
		{
			MHouseProperty->CanSellProperty = true;
		}
		else
		{
			MHouseProperty->CanSellProperty = false;
		}
	}
}

void AMP_GameMode::OfferTrade(
	AParticipantPawn* Player1,
	AParticipantPawn* Player2,
	FOffer offer)
{
	Log(FString::Format(TEXT("Trade --- {0} < - > {1}\n"), { Player1->GetParticipantName(), Player2->GetParticipantName() }));
	if (!Player2->IsBot()) return;

	bool need = true;
	bool enough = true;
	bool same_group = false;
	bool same_owner = false;

	TArray<int> PropertyPositions = {
		1, 3, 5, 6, 8, 9, 11, 13, 14, 15, 16, 18, 19, 21, 23, 24, 25, 26, 27, 29, 31, 32, 34, 35, 37, 39
	};

	if (offer.P2Receives.Num() > 0)
	{
		need = false;
		for (AMonopolyProperty* OfferProperty : offer.P2Receives)
		{
			int OfferPropPos = OfferProperty->GetPropertyPosition();
			int OfferArrPos = PropertyPositions.Find(OfferPropPos);

			if (OfferArrPos < 2 || OfferArrPos > 23)
			{
				int first = PropertyPositions[0], second = PropertyPositions[1];
				PropertyPositions.RemoveAt(0); PropertyPositions.RemoveAt(1);
				PropertyPositions.Add(first); PropertyPositions.Add(second);
				OfferArrPos = PropertyPositions.Find(OfferPropPos);
			}

			for (int start = OfferArrPos - 2; start < OfferArrPos + 2; start++)
			{
				if (start != OfferArrPos)
				{
					if (MonopolyProperties[start]->GetPropertyOwner() == OfferProperty->GetPropertyOwner())
					{
						same_owner = true;
						break;
					}
				}
			}

			AMonopolyHouseProperty* HProp = Cast<AMonopolyHouseProperty>(OfferProperty);
			if (HProp)
			{
				same_group = false;
				for (int start = OfferArrPos - 2; start < OfferArrPos + 2; start++)
				{
					if (start != OfferArrPos)
					{
						if (MonopolyProperties[start]->GetPropertyOwner() == OfferProperty->GetPropertyOwner())
						{
							AMonopolyHouseProperty* HPropOther = Cast<AMonopolyHouseProperty>(MonopolyProperties[start]);
							if (HPropOther)
							{
								if (HProp->GetPropGroup() == HPropOther->GetPropGroup())
								{
									same_group = true;
									break;
								}
							}
						}
					}
				}
				if (same_group && same_owner)
				{
					need = true;
				}
			}
			else if (same_owner)
			{
				need = true;
			}
		}
	}

	if (offer.P2ReceivesMoney > 0)
	{
		enough = false;
		if (offer.P1Receives.Num() == 0)
		{
			enough = true;
		}
		else
		{
			int Total = 0;
			for (AMonopolyProperty* OfferProperty : offer.P1Receives)
			{
				Total += FCString::Atoi(*OfferProperty->PriceToBuy());
			}

			if (offer.P2ReceivesMoney >= (Total / 2 + Total / 3))
			{
				enough = true;
			}
		}
	}

	if (enough && need)
	{
		if (offer.P1ReceivesMoney > 0)
		{
			Player2->Pay(offer.P1ReceivesMoney, Player1);
		}

		if (offer.P2ReceivesMoney > 0)
		{
			Player1->Pay(offer.P2ReceivesMoney, Player2);
		}

		for (AMonopolyProperty* OfferProperty : offer.P1Receives)
		{
			OfferProperty->SetPropertyOwner(Player1);
		}

		for (AMonopolyProperty* OfferProperty : offer.P2Receives)
		{
			OfferProperty->SetPropertyOwner(Player2);
		}
	}
}

void AMP_GameMode::SellUnnecesaryPropertiesAndBuyProperty(AParticipantPawn* Player, AMonopolyProperty* Property)
{
	int Total = 0;

	TArray<int> PropertyPositions = {
		1, 3, 6, 8, 9, 11, 13, 14, 16, 18, 19, 21, 23, 24, 26, 27, 29, 31, 32, 34, 37, 39
	};

	TArray<EPropGroups> Groups = {
		EPropGroups::Brown,
		EPropGroups::LightBlue,
		EPropGroups::Pink,
		EPropGroups::Orange,
		EPropGroups::Red,
		EPropGroups::Yellow,
		EPropGroups::Green,
		EPropGroups::DarkBlue
	};

	int PriceToBuy = FCString::Atoi(*Property->PriceToBuy());

	TArray<AMonopolyProperty*> PropsToSell;
	for (EPropGroups Group : Groups)
	{
		int max_group_prop = 0;
		int owned_group_props = 0;
		int value = 0;
		for (int Pos : PropertyPositions)
		{
			AMonopolyHouseProperty* HProp = Cast<AMonopolyHouseProperty>(MonopolyProperties[Pos]);
			if (HProp->GetPropGroup() == Group)
			{
				max_group_prop++;
				if (HProp->GetPropertyOwner() == Player)
				{
					owned_group_props++;
				}
			}
		}

		for (int Pos : PropertyPositions)
		{
			AMonopolyHouseProperty* HProp = Cast<AMonopolyHouseProperty>(MonopolyProperties[Pos]);
			if (HProp->GetPropGroup() == Group && owned_group_props == max_group_prop / 2)
			{
				if (HProp->GetPropertyOwner() == Player)
				{
					value += FCString::Atoi(*HProp->PriceToBuy()) / 2;
					PropsToSell.Add(HProp);
					break;
				}
			}
		}

		Total += value;

	}
	if (Player->GetMoney()->Total() + Total > PriceToBuy)
	{
		for (AMonopolyProperty* Prop : PropsToSell)
		{
			SellProperty(Prop->GetPropertyPosition(), Player);
		}
		BuyProperty(Property, Player);
	}
}

void AMP_GameMode::BuyHouseAI(AParticipantPawn* Player, AMonopolyProperty* prop)
{
	CalculateCanBuySellHouseOrProperty();
	bool CanBuyHouse = true;
	AMonopolyHouseProperty* Property = Cast<AMonopolyHouseProperty>(prop);
	TArray<AMonopolyHouseProperty*> SameGroupProps;
	TArray<int> SameGroupPropHousePrices;

	for (AMonopolyProperty* Prop : MonopolyProperties)
	{
		AMonopolyHouseProperty* HProp = Cast<AMonopolyHouseProperty>(Prop);
		if (HProp && HProp->GetPropGroup() == Property->GetPropGroup())
		{
			SameGroupProps.Add(HProp);
			SameGroupPropHousePrices.Add(FCString::Atoi(*(HProp->UpgradePrice())));
		}
	}

	Log(FString::Format(TEXT("BuyHouseAI CanBuyHouse before while: {0}\n"), { CanBuyHouse }));
	do
	{
		CanBuyHouse = false;
		for (AMonopolyHouseProperty* HProp : SameGroupProps)
		{
			if (UpgradePossible(HProp, Player)) {
				if (Player->GetMoney()->Total() > FCString::Atoi(*(HProp->UpgradePrice())))
				{
					UpgradeProperty(HProp, Player);
				}
			}
		}

		for (AMonopolyHouseProperty* HProp : SameGroupProps)
		{
			if (UpgradePossible(HProp, Player))
			{
				CanBuyHouse = true;
				break;
			}
		}
		Log(FString::Format(TEXT("BuyHouseAI CanBuyHouse at end of for: {0}\n"), { CanBuyHouse }));
	} while (CanBuyHouse);
}

void AMP_GameMode::BuyPropertyAI(AParticipantPawn* Player, AMonopolyProperty* Property)
{
	Log(FString::Format(TEXT("BuyPropertyAI --- {0} | {1}\n"), {Player->GetParticipantName(), Property->GetPropertyName()}));
	AMonopolyHouseProperty* HProperty = Cast<AMonopolyHouseProperty>(Property);
	EPropGroups group = HProperty->GetPropGroup();
	int PriceToBuy = FCString::Atoi(*HProperty->PriceToBuy());
	UMoney* Money = Player->GetMoney();
	int Total = Money->Total();

	if (Total < PriceToBuy)
	{
		bool IsLastPropNeeded = true;
		Log(FString("BuyPropertyAI --- NO MONEY\n"));
		for (AMonopolyProperty* prop : MonopolyProperties)
		{
			AMonopolyHouseProperty* hprop = Cast<AMonopolyHouseProperty>(prop);
			if (hprop)
			{
				if (hprop->GetPropGroup() == group)
				{
					Log(FString("BuyPropertyAI --- same group\n"));
					if (prop != Property)
					{
						Log(FString("BuyPropertyAI --- not same property\n"));
						if (prop->GetPropertyOwner() != Player)
						{
							if (hprop->GetPropertyOwner())
								Log(FString::Format(TEXT("BuyPropertyAI --- same group, property owner is not {0}\n"), {hprop->GetPropertyOwner()->GetParticipantName()}));
							IsLastPropNeeded = false;
							break;
						}
						else
						{
							Log(FString::Format(TEXT("BuyPropertyAI --- same group, property owner IS {0}\n"), { hprop->GetPropertyOwner()->GetParticipantName() }));
						}
					}
				}
			}
		}
		Log(FString::Format(TEXT("BuyPropertyAI --- LastPropNeeded = {0}\n"), {IsLastPropNeeded}));
		if (IsLastPropNeeded)
		{
			Log(FString::Format(TEXT("BuyPropertyAI --- {0} | {1} --- LastPropNeeded\n"), { Player->GetParticipantName(), Property->GetPropertyName() }));
			SellUnnecesaryPropertiesAndBuyProperty(Player, Property);
		}
		else
		{
			Log(FString("Buy propertyy AI over\n"));
		}
	}
	else
	{
		Log(FString("BuyPropertyAI --- Enough money\n"));
		if (Total > PriceToBuy * 2)
		{
			Log(FString::Format(TEXT("BuyPropertyAI --- {0} | Total money: {1} > 2 * {2}\n"), { Player->GetParticipantName(), Total, PriceToBuy }));
			BuyProperty(Property, Player);
		}
		else if (Total > PriceToBuy)
		{
			Log(FString::Format(TEXT("BuyPropertyAI --- {0} > {1}\n"), {Total, PriceToBuy}));
			for (AMonopolyProperty* prop : MonopolyProperties)
			{
				AMonopolyHouseProperty* hprop = Cast<AMonopolyHouseProperty>(prop);
				if (hprop && hprop != HProperty &&
					hprop->GetPropGroup() == HProperty->GetPropGroup() &&
					(!hprop->GetPropertyOwner() || hprop->GetPropertyOwner() == Player))
				{
					Log(FString::Format(TEXT("BuyPropertyAI --- {0} --- {1} > {2}\n"), { Player->GetParticipantName(), Total, PriceToBuy }));
					BuyProperty(Property, Player);
					break;
				}
			}
		}
	}
}

void AMP_GameMode::BuyRailroadAI(AParticipantPawn* Player, AMonopolyProperty* Property)
{
	FOffer offer;

	int PriceToBuy = FCString::Atoi(*Property->PriceToBuy());
	if (Player->GetMoney()->Total() > 500)
	{
		BuyProperty(Property, Player);
		for (int i = 5; i <= 35; i += 10)
		{
			if (i != Property->GetPropertyPosition() &&
				MonopolyProperties[i]->GetPropertyOwner() &&
				MonopolyProperties[i]->GetPropertyOwner() != Property->GetPropertyOwner())
			{
				offer.P1Receives = { MonopolyProperties[i] };
				offer.P2ReceivesMoney = 225;
				if (MonopolyProperties[i]->GetPropertyOwner()->IsBot())
					OfferTrade(Player, MonopolyProperties[i]->GetPropertyOwner(), offer);
				break;
			}
		}
	}
	else
	{
		for (int i = 5; i <= 35; i += 10)
		{
			if (MonopolyProperties[i] != Property &&
				(!MonopolyProperties[i]->GetPropertyOwner() ||
				MonopolyProperties[i]->GetPropertyOwner() == Player))
			{
				if (Player->GetMoney()->Total() > PriceToBuy)
					BuyProperty(Property, Player);
				else
					SellUnnecesaryPropertiesAndBuyProperty(Player, Property);
				break;
			}
		}
	}
}

void AMP_GameMode::BuyElectricAI(AParticipantPawn* Player, AMonopolyProperty* Property)
{
	FOffer offer;
	int PriceToBuy = FCString::Atoi(*Property->PriceToBuy());
	if (Player->GetMoney()->Total() > PriceToBuy)
	{
		BuyProperty(Property, Player);
		if (Property->GetPropertyPosition() == 12)
		{
			if (MonopolyProperties[28]->GetPropertyOwner() && (MonopolyProperties[28]->GetPropertyOwner()->IsBot()))
			{
				if (Player->GetMoney()->Total() >= FCString::Atoi(*MonopolyProperties[28]->PriceToBuy()))
				{
					offer.P1Receives = { MonopolyProperties[28] };
					offer.P2ReceivesMoney = FCString::Atoi(*MonopolyProperties[28]->PriceToBuy()) - 30;
					if (MonopolyProperties[28]->GetPropertyOwner()->IsBot())
						OfferTrade(Player, MonopolyProperties[28]->GetPropertyOwner(), offer);
				}
			}
		}
		else if (Property->GetPropertyPosition() == 28)
		{
			if (MonopolyProperties[12]->GetPropertyOwner() && (MonopolyProperties[12]->GetPropertyOwner()->IsBot()))
			{
				offer.P1Receives = { MonopolyProperties[12] };
				offer.P2ReceivesMoney = FCString::Atoi(*MonopolyProperties[12]->PriceToBuy()) - 30;
				if (MonopolyProperties[12]->GetPropertyOwner()->IsBot())
					OfferTrade(Player, MonopolyProperties[12]->GetPropertyOwner(), offer);
			}
		}
	}
}

void AMP_GameMode::HandleBotAI(AParticipantPawn* Player, AMonopolyProperty* Property)
{
	EType PropertyType = Property->GetPropertyType();

	switch (PropertyType)
	{
	case EType::Property:
		BuyPropertyAI(Player, Property);
		BuyHouseAI(Player, Property);
		break;
	case EType::Railroad:
		// 5 15 25 35
		BuyRailroadAI(Player, Property);
		break;
	case EType::Utility:
		// 12 28
		BuyElectricAI(Player, Property);
		break;
	default:
		break;
	}
}
