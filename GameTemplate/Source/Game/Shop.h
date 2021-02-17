#pragma once

#include "Framework/GameObject.h"

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
	ShopItem ShopItems[3];
};

