#include "Shop.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>

void Shop::OnInit()
{
	TitleText = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
}

void Shop::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	TitleText->SetOffset(MiddleX, 50);
	TitleText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	TitleText->SetText("Shop");

	//Weapon Upgrade
	ShopItem& WeaponUpgrade = ShopItems[0];
	WeaponUpgrade.ItemName = "Weapon Upgrade";
	WeaponUpgrade.ItemCost1 = 5;
	WeaponUpgrade.ItemCost2 = 10;
	WeaponUpgradeText->SetOffset(MiddleX * 0.3f, 200);
	WeaponUpgradeText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	WeaponUpgradeText->SetText(WeaponUpgrade.ItemName);
	WeaponUpgradeItemCostText->SetOffset(MiddleX * 0.3f, 250);
	WeaponUpgradeItemCostText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	WeaponUpgradeItemCostText->SetText("Cost: " + to_string(WeaponUpgrade.ItemCost1));
	WeaponUpgradeUserPrompt->SetOffset(MiddleX * 0.3f, 500);
	WeaponUpgradeUserPrompt->SetFont("Fonts/Boxy-Bold.ttf", 20);
	WeaponUpgradeUserPrompt->SetText("Press 1 To Buy");

	//Speed Upgrade
	ShopItem& SpeedUpgrade = ShopItems[1];
	SpeedUpgrade.ItemName = "Speed Upgrade";
	SpeedUpgrade.ItemCost1 = 2;
	SpeedUpgrade.ItemCost2 = 8;
	SpeedUpgradeText->SetOffset(MiddleX, 200);
	SpeedUpgradeText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	SpeedUpgradeText->SetText(SpeedUpgrade.ItemName);
	SpeedUpgradeItemCostText->SetOffset(MiddleX, 250);
	SpeedUpgradeItemCostText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	SpeedUpgradeItemCostText->SetText("Cost: " + to_string(SpeedUpgrade.ItemCost1));
	SpeedUpgradeUserPrompt->SetOffset(MiddleX, 500);
	SpeedUpgradeUserPrompt->SetFont("Fonts/Boxy-Bold.ttf", 20);
	SpeedUpgradeUserPrompt->SetText("Press 2 To Buy");

	//Health Upgrade
	ShopItem& HealthUpgrade = ShopItems[2];
	HealthUpgrade.ItemName = "Health Upgrade";
	HealthUpgrade.ItemCost1 = 10;
	HealthUpgrade.ItemCost2 = 20;
	HealthUpgradeText->SetOffset(MiddleX * 1.75f, 200);
	HealthUpgradeText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	HealthUpgradeText->SetText(HealthUpgrade.ItemName);
	HealthUpgradeItemCostText->SetOffset(MiddleX * 1.75f, 250);
	HealthUpgradeItemCostText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	HealthUpgradeItemCostText->SetText("Cost: " + to_string(HealthUpgrade.ItemCost1));
	HealthUpgradeUserPrompt->SetOffset(MiddleX * 1.75f, 500);
	HealthUpgradeUserPrompt->SetFont("Fonts/Boxy-Bold.ttf", 20);
	HealthUpgradeUserPrompt->SetText("Press 3 To Buy");

}

void Shop::OnShutdown()
{
    delete TitleText;
    TitleText = nullptr;
}