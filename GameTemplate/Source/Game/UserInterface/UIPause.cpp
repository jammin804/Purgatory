#include "UIPause.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>

void UIPause::OnInit()
{
	PauseText = GameComponent::CreateInstance<TextComponent>(this);
}

void UIPause::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	PauseText->SetOffset(MiddleX, MiddleY - 150);
	PauseText->SetFont("Fonts/Boxy-Bold.ttf", FontSize);

	PauseText->SetText("Paused");
}
