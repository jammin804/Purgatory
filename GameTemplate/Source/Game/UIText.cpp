#include "UIText.h"

#include "Framework/TextComponent.h"
#include "Framework/Globals.h"
#include <stdio.h>

void UIText::OnInit()
{
	TopLeftText = GameComponent::CreateInstance<TextComponent>(this);
	TopCenterText = GameComponent::CreateInstance<TextComponent>(this);
	TopRightText = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine1 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine2 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine3 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine4 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine5 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine6 = GameComponent::CreateInstance<TextComponent>(this);
	MiddleTextLine7 = GameComponent::CreateInstance<TextComponent>(this);
}

void UIText::OnPostInit()
{
	TopLeftText->SetOffset(100, 50);
	float MiddleX = Globals::WindowSizeX * 0.5f;
	float MiddleY = Globals::WindowSizeY * 0.5f;
	TopCenterText->SetOffset(MiddleX, 50);
	TopRightText->SetOffset(Globals::WindowSizeX - 100, 50);
	MiddleTextLine1->SetOffset(MiddleX, MiddleY - 250);
	MiddleTextLine2->SetOffset(MiddleX, MiddleY - 200);
	MiddleTextLine3->SetOffset(MiddleX, MiddleY - 150);
	MiddleTextLine4->SetOffset(MiddleX, MiddleY - 100);
	MiddleTextLine5->SetOffset(MiddleX, MiddleY - 50);
	MiddleTextLine6->SetOffset(MiddleX, MiddleY + 50);
	MiddleTextLine7->SetOffset(MiddleX, MiddleY + 100);
	TopCenterText->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	TopRightText->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine1->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine2->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine3->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine4->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine5->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine6->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	MiddleTextLine7->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
}

void UIText::OnShutdown()
{
    delete TopLeftText;
    TopLeftText = nullptr;

    delete TopCenterText;
    TopCenterText = nullptr;

    delete TopRightText;
    TopRightText = nullptr;

    delete MiddleTextLine1;
    MiddleTextLine1 = nullptr;

    delete MiddleTextLine2;
    MiddleTextLine2 = nullptr;

    delete MiddleTextLine3;
    MiddleTextLine3 = nullptr;

	delete MiddleTextLine4;
	MiddleTextLine4 = nullptr;

	delete MiddleTextLine5;
	MiddleTextLine5 = nullptr;

	delete MiddleTextLine6;
	MiddleTextLine6 = nullptr;

	delete MiddleTextLine7;
	MiddleTextLine7 = nullptr;
}

void UIText::SetWelcomeToTheGame()
{
    TopLeftText->SetVisible(false);
    TopRightText->SetVisible(false);
    TopCenterText->SetVisible(false);
    MiddleTextLine1->SetVisible(true);
    MiddleTextLine2->SetVisible(true);
    MiddleTextLine3->SetVisible(true);
	MiddleTextLine4->SetVisible(true);
	MiddleTextLine5->SetVisible(true);
	MiddleTextLine6->SetVisible(true);
	MiddleTextLine6->SetVisible(true);

    MiddleTextLine1->SetText("Welcome To Purgatory, fallen Priest! Since you have disgraced the eye of the Lord,");
	MiddleTextLine2->SetText("I (Saint Peters) will give you a second chance to redeem yourself.");
	MiddleTextLine3->SetText("Exorcise as many demons as you can! Your performance will be judge ");
	MiddleTextLine4->SetText("to see if you can come into the kingdom of the Lord.");
	MiddleTextLine5->SetText("Good Luck. Press Enter To Start");
	MiddleTextLine6->SetText("Use the ""Arrow Keys"" to move and the ""Space"" button to fire lasers");
}

void UIText::SetInGame()
{
    TopLeftText->SetVisible(true);
    TopRightText->SetVisible(true);
    TopCenterText->SetVisible(true);
    MiddleTextLine1->SetVisible(false);
    MiddleTextLine2->SetVisible(false);
    MiddleTextLine3->SetVisible(false);
	MiddleTextLine4->SetVisible(false);
	MiddleTextLine5->SetVisible(false);
	MiddleTextLine6->SetVisible(false);
}

void UIText::SetGameOver(int FinalScore)
{
    TopLeftText->SetVisible(false);
    TopRightText->SetVisible(false);
    TopCenterText->SetVisible(false);
    MiddleTextLine1->SetVisible(true);
    MiddleTextLine2->SetVisible(true);
    MiddleTextLine3->SetVisible(true);

    MiddleTextLine1->SetText("GAME OVER");
   /* char FinalScoreStr[50];
    sprintf_s(FinalScoreStr, "Final Score: %d", FinalScore);
    MiddleTextLine2->SetText(FinalScoreStr);*/
    MiddleTextLine3->SetText("Press Enter To Quit");
}

void UIText::SetGamePaused()
{
	TopLeftText->SetVisible(false);
	TopRightText->SetVisible(false);
	TopCenterText->SetVisible(false);
	MiddleTextLine1->SetVisible(false);
	MiddleTextLine2->SetVisible(false);
	MiddleTextLine3->SetVisible(true);
	
	MiddleTextLine3->SetText("Paused");
}

void UIText::SetYouSurvived(int FinalScore)
{
    TopLeftText->SetVisible(false);
    TopRightText->SetVisible(false);
    TopCenterText->SetVisible(false);
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
    //char LivesLeft[50];
    /*sprintf_s(LivesLeft, "Lives Left: %d", NewLivesLeft);
    TopLeftText->SetText(LivesLeft);*/
}

void UIText::UpdateTimeRemaining(int NewTimeMins, int NewTimeSeconds)
{
    char LivesLeft[50];
   /* if (NewTimeMins > 0)
    {
        sprintf_s(LivesLeft, "Time Left: %d:%s%d", NewTimeMins, NewTimeSeconds < 10 ? "0" : "", NewTimeSeconds);
    }
    else
    {
        sprintf_s(LivesLeft, "Time Left: %ds", NewTimeSeconds);
    }*/
    TopCenterText->SetText(LivesLeft);
}
