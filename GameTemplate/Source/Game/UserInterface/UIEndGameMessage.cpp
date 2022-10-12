#include "UIEndGameMessage.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>


void UIEndGameMessage::OnInit()
{
	for (int i = 0; i < COUNT; i++)
	{
		EndGameMessageText[i] = GameComponent::CreateInstance<TextComponent>(this);
	}
}

void UIEndGameMessage::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;

	EndGameMessageText[Middle1]->SetOffset(MiddleX, MiddleY - 250);
	EndGameMessageText[Middle2]->SetOffset(MiddleX, MiddleY - 150);

	for (int i = 0; i < COUNT; i++)
	{
		EndGameMessageText[i]->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	}

	if (bDidSurvive)
	{
		EndGameMessageText[Middle1]->SetText("Congratulations! You survived the night!");

	}
	else
	{
		EndGameMessageText[Middle1]->SetText("GAME OVER");

	}
	EndGameMessageText[Middle2]->SetText("Press Enter To Quit");

}

void UIEndGameMessage::SetDidSurvive(bool bSurvive)
{
	bDidSurvive = bSurvive;
}
