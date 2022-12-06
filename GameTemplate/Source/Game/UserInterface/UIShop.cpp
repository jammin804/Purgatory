#include "UIShop.h"
#include "Framework/Globals.h"
#include "Framework/ImageComponent.h"
#include "Framework/TextComponent.h"
#include "Game/Player.h"
#include <stdio.h>

void UIShop::OnInit()
{
	TitleText = GameComponent::CreateInstance<TextComponent>(this);
	CoinText = GameComponent::CreateInstance<TextComponent>(this);
	ContinueText = GameComponent::CreateInstance<TextComponent>(this);

	WeaponUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
	WeaponUpgradeImage = GameComponent::CreateInstance<ImageComponent>(this);
	SpeedUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
	SpeedUpgradeImage = GameComponent::CreateInstance<ImageComponent>(this);
	HealthUpgradeText = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeItemCostText = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeUserPrompt = GameComponent::CreateInstance<TextComponent>(this);
	HealthUpgradeImage = GameComponent::CreateInstance<ImageComponent>(this);
}

void UIShop::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	int CurrentNumberOfCoins = 0;
	
	
	TitleText->SetOffset(MiddleX, 50);
	TitleText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	TitleText->SetText("Shop");

	
	CoinText->SetOffset(MiddleX, 150);
	CoinText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	CoinText->SetText("Coins: " + to_string(CurrentNumberOfCoins)); // Need to pull in players money
	UpdateCoinShopText();

	ContinueText->SetOffset(MiddleX, 575);
	ContinueText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	ContinueText->SetText("Press Enter to exit.");


	int CoinsCollected = player->GetNumberOfCoins();
	CoinText->SetText("Coins: 0" + to_string(CoinsCollected));
	
	
	


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
	WeaponUpgradeUserPrompt->SetOffset(MiddleX * 0.3f, 500);
	WeaponUpgradeUserPrompt->SetFont("Fonts/Boxy-Bold.ttf", 20);
	WeaponUpgradeUserPrompt->SetText("Press 1 To Buy");
	WeaponUpgradeImage->SetScale(3.0f);
	WeaponUpgradeImage->SetOffset(MiddleX * 0.3f, 400);
	WeaponUpgradeItemCostText->SetText("Cost: " + to_string(WeaponUpgrade.ItemCost1));
	WeaponUpgradeImage->LoadImage("Art/PowerUpIcon-WeaponBurst.png");

	
	UpgradeWeaponLevel(WeaponUpgrade);

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

	SpeedUpgradeImage->LoadImage("Art/PowerUpIcon-Speed1.png");
	SpeedUpgradeImage->SetScale(3.0f);
	SpeedUpgradeImage->SetOffset(MiddleX, 400);

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

	HealthUpgradeImage->LoadImage("Art/PowerUpIcon-Health1.png");
	HealthUpgradeImage->SetScale(3.0f);
	HealthUpgradeImage->SetOffset(MiddleX  * 1.75f, 400);

}

void UIShop::UpdateCoinShopText()
{
	if (player)
	{
		char CoinsCollected[10];
		sprintf_s(CoinsCollected, "Coins: %d", player->GetNumberOfCoins());
		CoinText->SetText(CoinsCollected);
	}
}

void UIShop::UpgradeWeaponLevel(const ShopItem& WeaponUpgrade)
{
	if (player)
	{
		if (player->WeaponLevel == 1)
		{
			WeaponUpgradeItemCostText->SetText("Cost: " + to_string(WeaponUpgrade.ItemCost2));
			WeaponUpgradeImage->LoadImage("Art/PowerUpIcon-WeaponCirlce.png");
		}
		if (player->WeaponLevel == 2)
		{
			WeaponUpgradeItemCostText->SetText("N/A Fully Upgraded");
			WeaponUpgradeImage->LoadImage("Art/PowerUpIcon-NA.png");
		}
	}
	
	
}

void UIShop::UpgradeSpeedLevel(const ShopItem& SpeedUpgrade)
{
	if (player)
	{
		if (player->SpeedLevel == 1)
		{
			SpeedUpgradeItemCostText->SetText("Cost: " + to_string(SpeedUpgrade.ItemCost2));
			SpeedUpgradeImage->LoadImage("Art/PowerUpIcon-Speed2.png");
		}
		if (player->SpeedLevel == 2)
		{
			SpeedUpgradeItemCostText->SetText("N/A Fully Upgraded");
			SpeedUpgradeImage->LoadImage("Art/PowerUpIcon-NA.png");
		}
	}
}

void UIShop::UpgradeHealthLevel(const ShopItem& HealthUpgrade)
{
	if (player)
	{
		if (player->HealthLevel == 1)
		{
			HealthUpgradeItemCostText->SetText("Cost: " + to_string(HealthUpgrade.ItemCost2));
			HealthUpgradeImage->LoadImage("Art/PowerUpIcon-WeaponCircle.png");
		}
		if (player->HealthLevel == 2)
		{
			HealthUpgradeItemCostText->SetText("N/A Fully Upgraded");
			HealthUpgradeImage->LoadImage("Art/PowerUpIcon-NA.png");
		}
	}
}
