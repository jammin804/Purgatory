#include "UIWelcomeMessage.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>


void UIWelcomeMessage::OnInit()
{
	for (int i = 0; i < COUNT; i++)
	{
		WelcomeText[i] = GameComponent::CreateInstance<TextComponent>(this);
	}

}

void UIWelcomeMessage::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	WelcomeText[Middle1]->SetOffset(MiddleX, MiddleY - 250);
	WelcomeText[Middle2]->SetOffset(MiddleX, MiddleY - 200);
	WelcomeText[Middle3]->SetOffset(MiddleX, MiddleY - 150);
	WelcomeText[Middle4]->SetOffset(MiddleX, MiddleY - 100);
	WelcomeText[Middle5]->SetOffset(MiddleX, MiddleY - 50);
	WelcomeText[Middle6]->SetOffset(MiddleX, 450);
	WelcomeText[BottomCenter]->SetOffset(MiddleX, 575);

	for (int i = 0; i < COUNT; i++)
	{
		WelcomeText[i]->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	}

	WelcomeText[Middle1]->SetText("Welcome To Purgatory, fallen Priest! Since you have disgraced the eye of the Lord,");
	WelcomeText[Middle2]->SetText("I (Saint Peters) will give you a second chance to redeem yourself.");
	WelcomeText[Middle3]->SetText("Exorcise as many demons as you can! Your performance will be judge ");
	WelcomeText[Middle4]->SetText("to see if you can come into the kingdom of the Lord.");
	WelcomeText[Middle5]->SetText("Good Luck.");
	WelcomeText[Middle6]->SetText("Press Enter To Start");
	WelcomeText[BottomCenter]->SetText("Use the ""Arrow Keys"" to move and the ""Space"" button to fire lasers");
}