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

    public:
        Coin* CreateCoin(); //Changed Splits Left to Max Enemy Health
        vector<Coin*>& GetCoins() { return Coins; }
private:
        vector<Coin*> Coins;
};