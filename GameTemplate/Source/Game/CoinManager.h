#pragma once

#include "Framework/GameObject.h"
#include <vector>

class Coin;

using namespace std;

class CoinManager : public GameObject
{
    protected:
        virtual void OnInit() override;
        virtual void OnUpdate(float DeltaTime) override;

		virtual void OnRestart() override;
		virtual void SetEnabled(bool bEnabled) override;
public:
        Coin* CreateCoin(float posX, float posY); //Changed Splits Left to Max Enemy Health

		vector<Coin*>& GetCoins() { return Coins; }
private:
        vector<Coin*> Coins;
};