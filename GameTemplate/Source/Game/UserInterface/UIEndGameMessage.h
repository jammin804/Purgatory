#pragma once

#pragma once

#include "Framework/GameObject.h"

using namespace std;

class TextComponent;

class UIEndGameMessage : public GameObject
{
protected:
	virtual void OnInit() override;
	virtual void OnPostInit() override;

public:
	void SetDidSurvive(bool bSurvive);

private:
	enum TextName
	{
		Middle1 = 0,
		Middle2,
		COUNT
	};
	TextComponent* EndGameMessageText[COUNT] = { nullptr };
	bool bDidSurvive = false;
	int FontSize = 18;
};