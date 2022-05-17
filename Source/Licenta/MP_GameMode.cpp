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

void AMP_GameMode::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("MP_GameMode Initialization"));
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
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRS"))->Initialize(pos++, "Railroad South", EActions::RailroadS, "/RailroadReading"),
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
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRW"))->Initialize(pos++, "Railroad West", EActions::RailroadW, "/RailroadPennsylvania"),
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
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRN"))->Initialize(pos++, "Railroad North", EActions::RailroadN, "/RailroadBO"),
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
		NewObject<ARailroad>(GetTransientPackage(), TEXT("RRE"))->Initialize(pos++, "Railroad East", EActions::RailroadE, "/RailroadShortLine"),
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
		NewObject<ACard>(GetTransientPackage(), TEXT("Inheritance"))->Initialize("ou inherit $100", ECardActions::Get, 10, 0, 0)
	};
	GenerateHouses();
}

void AMP_GameMode::StartGame(APlayerController* PlayerController, TArray<UStaticMesh*> StaticMeshList, TArray<UMaterial*> Materials)
{
	GeneratePlayers(PlayerController, StaticMeshList, Materials);
	HandlePlayMenu(true, MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()]);
	HandlePropertyInfo(MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()], Players[PlayerTurn]);
	HandleMoneyInfo(Players[PlayerTurn]->Money);
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
	UE_LOG(LogTemp, Log, TEXT("ExecuteBotTurn -> PlayerTurn: %d"), PlayerTurn);
	if (IsValid(Players[PlayerTurn]))
	{
		UE_LOG(LogTemp, Log, TEXT("ExecuteBotTurn -> VALID Players[PlayerTurn]"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ExecuteBotTurn -> INVALID Players[PlayerTurn]"));
	}
	AAIPawn* Bot = Cast<AAIPawn>(Players[PlayerTurn]);
	if (Bot && Bot->IsBot())
	{
		UE_LOG(LogTemp, Log, TEXT("ExecuteBotTurn -> VALID Bot"));
		LastDiceRolled = Bot->Play();

		NextPlayerTurn();
		Bot = Cast<AAIPawn>(Players[PlayerTurn]);
		if (Bot && Bot->IsBot())
		{
			ExecuteBotTurn();
		}
		else
		{
			HandlePlayMenu(true, MonopolyProperties[Players[PlayerTurn]->GetPlayerPosition()]);
			HandleMoneyInfo(Players[PlayerTurn]->Money);
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("ExecuteBotTurn -> INVALID Bot"));
	}
}

AMonopolyProperty* AMP_GameMode::ExecutePlayerTurn()
{
	UE_LOG(LogTemp, Log, TEXT("ExecutePlayerTurn -> PlayerTurn: %d"), PlayerTurn);
	if (IsValid(Players[PlayerTurn]))
	{
		UE_LOG(LogTemp, Log, TEXT("ExecutePlayerTurn -> VALID Players[PlayerTurn]"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ExecutePlayerTurn -> INVALID Players[PlayerTurn]"));
	}
	
	AParticipantPawn* Participant = Players[PlayerTurn];
	APlayerPawn* Player = Cast<APlayerPawn>(Participant);
	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("ExecutePlayerTurn -> VALID Player"));
		LastDiceRolled = Player->Play();
		Player->SetRolled(true);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("ExecutePlayerTurn -> INVALID Player"));
	}

	int Position = Player->GetPlayerPosition();
	HandlePlayMenu(false, MonopolyProperties[Position]);
	HandlePropertyInfo(MonopolyProperties[Position], Participant);
	return GetProperty(Position);
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
		PlayMenu->GetPayScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
		PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
		// If property is tax => show payscalebox
	}
}

void AMP_GameMode::HandleOwnedProperty(AMonopolyProperty* Property, AParticipantPawn* Participant)
{
	AParticipantPawn* PropertyOwner = Property->GetPropertyOwner();

	if (IsValid(PropertyOwner))
	{
		PlayMenu->GetOwner()->SetText(UKismetTextLibrary::Conv_StringToText(PropertyOwner->ParticipantName));
		if (PropertyOwner == Participant)
		{
			PlayMenu->GetUpgrade()->SetText(UKismetTextLibrary::Conv_StringToText(Property->UpgradePrice()));

			PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(""));
			PlayMenu->GetPrice()->SetText(UKismetTextLibrary::Conv_StringToText(""));
			// hide buy button, hide pay button, show upgrade button if satisfies conditions, show sell button
			PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			PlayMenu->GetPayScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			// if conditions are met to upgrade/buy house, show upgrade button
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
			// hide buy button, show pay button if has enough money, show possibility to sell current participant properties if
			// that way can have enough money to pay, else, end game for participant
			PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
			PlayMenu->GetPayScaleBox()->SetVisibility(ESlateVisibility::Visible);
			PlayMenu->GetUpgradeScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		PlayMenu->GetOwner()->SetText(UKismetTextLibrary::Conv_StringToText(""));
		PlayMenu->GetPay()->SetText(UKismetTextLibrary::Conv_StringToText(""));
		PlayMenu->GetPrice()->SetText(UKismetTextLibrary::Conv_StringToText(Property->PriceToBuy()));
		PlayMenu->GetUpgrade()->SetText(UKismetTextLibrary::Conv_StringToText(Property->UpgradePrice()));
		// Show buy button here, hide pay button, hide sell button
		PlayMenu->GetBuyScaleBox()->SetVisibility(ESlateVisibility::Visible);
		PlayMenu->GetPayScaleBox()->SetVisibility(ESlateVisibility::Collapsed);
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

void AMP_GameMode::BuyProperty()
{
	AParticipantPawn *Player = GetParticipant();
	AMonopolyProperty* Property = MonopolyProperties[Player->GetPlayerPosition()];

	Player->Pay(FCString::Atoi(*Property->PriceToBuy()));

	Property->SetPropertyOwner(Player);
	HandlePropertyInfo(Property, Player);
	HandleMoneyInfo(Player->GetMoney());
}

void AMP_GameMode::SellProperty(const int Position)
{
	AParticipantPawn* Player = GetParticipant();
	AMonopolyProperty* Property = MonopolyProperties[Position];

	Player->Receive(FCString::Atoi(*Property->PriceToSell()));
	Property->ResetInit();
	HandlePropertyInfo(Property, Player);
	HandleMoneyInfo(Player->GetMoney());
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

void AMP_GameMode::UpgradeProperty(AMonopolyProperty* Property)
{
	//Property = GetProperty(GetParticipant()->GetPlayerPosition());
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
	HandlePropertyInfo(Property, GetParticipant());
	HandleMoneyInfo(GetParticipant()->GetMoney());
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

	APlayerPawn* Player = Cast<APlayerPawn>(GetParticipant());
	Player->CheatMove();
}
