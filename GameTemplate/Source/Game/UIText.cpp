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
}

void UIText::OnPostInit()
{
    TopLeftText->SetOffset(100, 50);
    float MiddleX = Globals::WindowSizeX * 0.5f;
    float MiddleY = Globals::WindowSizeY * 0.5f;
    TopCenterText->SetOffset(MiddleX, 50);
    TopRightText->SetOffset(Globals::WindowSizeX - 100, 50);
    MiddleTextLine1->SetOffset(MiddleX, MiddleY - 150);
    MiddleTextLine2->SetOffset(MiddleX, MiddleY - 100);
    MiddleTextLine3->SetOffset(MiddleX, MiddleY - 50);
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
}

void UIText::SetWelcomeToTheGame()
{
    TopLeftText->SetVisible(false);
    TopRightText->SetVisible(false);
    TopCenterText->SetVisible(false);
    MiddleTextLine1->SetVisible(true);
    MiddleTextLine2->SetVisible(true);
    MiddleTextLine3->SetVisible(false);

    MiddleTextLine1->SetText("Welcome To Asteroids! Press Enter To Start");
    MiddleTextLine2->SetText("Use the ""Arrow Keys"" to move and the ""Space"" button to fire lasers");
}

void UIText::SetInGame()
{
    TopLeftText->SetVisible(true);
    TopRightText->SetVisible(true);
    TopCenterText->SetVisible(true);
    MiddleTextLine1->SetVisible(false);
    MiddleTextLine2->SetVisible(false);
    MiddleTextLine3->SetVisible(false);
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
    char FinalScoreStr[50];
    sprintf_s(FinalScoreStr, "Final Score: %d", FinalScore);
    MiddleTextLine2->SetText(FinalScoreStr);
    MiddleTextLine3->SetText("Press Enter To Quit");
}

void UIText::SetYouSurvived(int FinalScore)
{
    TopLeftText->SetVisible(false);
    TopRightText->SetVisible(false);
    TopCenterText->SetVisible(false);
    MiddleTextLine1->SetVisible(true);
    MiddleTextLine2->SetVisible(true);
    MiddleTextLine3->SetVisible(true);

    MiddleTextLine1->SetText("Congratulations! You survived!");
    char FinalScoreStr[50];
    sprintf_s(FinalScoreStr, "Final Score: %d", FinalScore);
    MiddleTextLine2->SetText(FinalScoreStr);
    MiddleTextLine3->SetText("Press Enter To Quit");
}

void UIText::UpdateScore(int NewScore)
{
    char Score[50];
    sprintf_s(Score, "Score: %d", NewScore);
    TopRightText->SetText(Score);
}

void UIText::UpdateLivesLeft(int NewLivesLeft)
{
    char LivesLeft[50];
    sprintf_s(LivesLeft, "Lives Left: %d", NewLivesLeft);
    TopLeftText->SetText(LivesLeft);
}

void UIText::UpdateTimeRemaining(int NewTimeMins, int NewTimeSeconds)
{
    char LivesLeft[50];
    if (NewTimeMins > 0)
    {
        sprintf_s(LivesLeft, "Time Left: %d:%s%d", NewTimeMins, NewTimeSeconds < 10 ? "0" : "", NewTimeSeconds);
    }
    else
    {
        sprintf_s(LivesLeft, "Time Left: %ds", NewTimeSeconds);
    }
    TopCenterText->SetText(LivesLeft);
}
