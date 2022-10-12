#pragma once

#pragma once

#include "Framework/GameObject.h"

using namespace std;

class TextComponent;

class UIPause : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;

public:

private:

	TextComponent* PauseText = nullptr;
	int FontSize = 18;
};