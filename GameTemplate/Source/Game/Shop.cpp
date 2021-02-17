#include "Shop.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>

void Shop::OnInit()
{
	TitleText = GameComponent::CreateInstance<TextComponent>(this);
}

void Shop::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	TitleText->SetOffset(MiddleX, 50);
	TitleText->SetFont("Fonts/Boxy-Bold.ttf", 20);
	TitleText->SetText("Shop");

	ShopItem& WeaponUpgrade = ShopItems[0];
	WeaponUpgrade.ItemName = "Weapon Upgrade";
	WeaponUpgrade.ItemCost1 = 5;
	WeaponUpgrade.ItemCost2 = 10;
}

void Shop::OnShutdown()
{
    delete TitleText;
    TitleText = nullptr;
}