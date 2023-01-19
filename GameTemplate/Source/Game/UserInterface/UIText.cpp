#include "UIText.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>

void UIText::OnInit()
{
	MiddleTextLine1 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine2 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine3 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine4 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine5 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine6 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine7 = GameComponent::CreateInstance<TextComponent>(this);
	BottomCenterText = GameComponent::CreateInstance<TextComponent>(this);
}

void UIText::OnPostInit()
{
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	MiddleTextLine1->SetOffset(MiddleX, MiddleY - 250);
	MiddleTextLine2->SetOffset(MiddleX, MiddleY - 200);
	MiddleTextLine3->SetOffset(MiddleX, MiddleY - 150);
	MiddleTextLine4->SetOffset(MiddleX, MiddleY - 100);
	MiddleTextLine5->SetOffset(MiddleX, MiddleY - 50);
	MiddleTextLine6->SetOffset(MiddleX, 450);
	MiddleTextLine7->SetOffset(MiddleX, MiddleY + 100);
	BottomCenterText->SetOffset(MiddleX, 575);
	MiddleTextLine1->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine2->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine3->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine4->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine5->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine6->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine7->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	BottomCenterText->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
}


//void UIText::SetGameOver(int FinalScore)
//{
//    TopRightText->SetVisible(false);
//    TopCenterText->SetVisible(false);
//    MiddleTextLine1->SetVisible(true);
//    MiddleTextLine2->SetVisible(true);
//    MiddleTextLine3->SetVisible(true);
//
//    MiddleTextLine1->SetText("GAME OVER");
//   /* char FinalScoreStr[50];
//    sprintf_s(FinalScoreStr, "Final Score: %d", FinalScore);
//    MiddleTextLine2->SetText(FinalScoreStr);*/
//    MiddleTextLine3->SetText("Press Enter To Quit");
//}



void UIText::SetYouSurvived(int FinalScore)
{
    MiddleTextLine1->SetVisible(true);
    MiddleTextLine2->SetVisible(true);
    MiddleTextLine3->SetVisible(true);

    MiddleTextLine1->SetText("Congratulations! You survived the night!");
   /* char FinalScoreStr[50];
    sprintf_s(FinalScoreStr, "Final Score: %d", FinalScore);
    MiddleTextLine2->SetText(FinalScoreStr);*/
    MiddleTextLine3->SetText("Press Enter To Quit");
}

void UIText::UpdateScore(int NewScore)
{
   /* char Score[50];
    sprintf_s(Score, "Score: %d", NewScore);
    TopRightText->SetText(Score);*/
}

void UIText::UpdateLivesLeft(int NewLivesLeft)
{
   /* char LivesLeft[50];
    sprintf_s(LivesLeft, "Lives Left: %d", NewLivesLeft);*/
   // TopLeftText->SetText();
}