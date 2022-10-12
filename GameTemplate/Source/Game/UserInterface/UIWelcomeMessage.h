#pragma once

#include "Framework/GameObject.h"

using namespace std;

class TextComponent;

class UIWelcomeMessage : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;

public:

private:
	enum TextName
	{
		Middle1 = 0,
		Middle2,
		Middle3,
		Middle4,
		Middle5,
		Middle6,
		BottomCenter,
		COUNT
	};
	TextComponent* WelcomeText[COUNT] = {nullptr};
	int FontSize = 18;
};