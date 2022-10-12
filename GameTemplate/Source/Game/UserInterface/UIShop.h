#pragma once

#include "Framework/GameObject.h"
#include "Game/Player.h"
#include "Framework/EString.h"

using namespace std;
struct ShopItem
{
	EString ItemName;
	EString ItemDescrption1;
	EString ItemDescrption2;
	EString ItemImage1;
	EString ItemImage2;
	EString ItemImageFull;
	int ItemCost1;
	int ItemCost2;
	int NumberBought = 0;
};
class TextComponent;
class ImageComponent;
class Player;

class UIShop : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnPostInit() override;

public:
	const ShopItem* GetShopItems() const { return ShopItems; }
	void UpgradeWeaponLevel(const ShopItem& WeaponUpgrade);
	void UpgradeSpeedLevel(const ShopItem& SpeedUpgrade);
	void UpgradeHealthLevel(const ShopItem& HealthUpgrade);
	void SetPlayer(const Player* NewPlayer) { player = NewPlayer; }
	void UpdateCoinShopText();
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

