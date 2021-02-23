#pragma once

#include "Framework/GameObject.h"
#include "Player.h"

using namespace std;
struct ShopItem
{
	string ItemName;
	string ItemDescrption1;
	string ItemDescrption2;
	string ItemImage1;
	string ItemImage2;
	string ItemImageFull;
	int ItemCost1;
	int ItemCost2;
	int NumberBought = 0;
};
class TextComponent;
class ImageComponent;
class Player;

class Shop : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;
    virtual void OnShutdown() override;

public:
	const ShopItem* GetShopItems() const { return ShopItems; }
private:
    TextComponent* TitleText = nullptr;
	TextComponent* CoinText = nullptr;
	TextComponent* WeaponUpgradeText = nullptr;
	TextComponent* WeaponUpgradeItemCostText = nullptr;
	TextComponent* WeaponUpgradeUserPrompt = nullptr;
	ImageComponent* WeaponUpgradeImage = nullptr;
	TextComponent* SpeedUpgradeText = nullptr;
	TextComponent* SpeedUpgradeItemCostText = nullptr;
	TextComponent* SpeedUpgradeUserPrompt = nullptr;
	ImageComponent* SpeedUpgradeImage = nullptr;
	TextComponent* HealthUpgradeText = nullptr;
	TextComponent* HealthUpgradeItemCostText = nullptr;
	TextComponent* HealthUpgradeUserPrompt = nullptr;
	ImageComponent* HealthUpgradeImage = nullptr;
	ShopItem ShopItems[3];
	const Player* player = nullptr;

};

