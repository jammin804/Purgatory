#include "GameFlow.h"
#include "Framework/InputComponent.h"
#include "UIText.h"

void GameFlow::OnInit()
{
    Input = new InputComponent(this);
    GameUI = new UIText();
}

void GameFlow::OnPostInit()
{
    if (GameUI)
    {
        //GameUI->SetWelcomeToTheGame();
    }

    for (GameObject* Object : ObjectsToDisableAtStart)
    {
        Object->SetEnabled(false);
    }
}

void GameFlow::OnUpdate(float DeltaTime)
{
    switch (CurrentState)
    {
    case EState::Starting:
        if (Input)
        {
            if (Input->IsKeyPressed(ALLEGRO_KEY_ENTER))
            {
                bReturnPressed = true;
            }
            if (bReturnPressed && Input->IsKeyReleased(ALLEGRO_KEY_ENTER))
            {
                CurrentState = EState::InGame;
                for (GameObject* Object : ObjectsToDisableAtStart)
                {
                    Object->SetEnabled(true);
                }
                if (GameUI)
                {
                    //GameUI->SetInGame();
                }
            }
        }
        break;
    case EState::InGame:
        TimeRemaining -= DeltaTime;
        if (GameUI)
        {
            //GameUI->UpdateTimeRemaining((int)TimeRemaining / 60, (int)TimeRemaining% 60);
        }
        if (TimeRemaining <= 0.0f)
        {
            CurrentState = EState::Ending;
            if (GameUI)
            {
                //GameUI->SetYouSurvived(CurrentScore);
            }
        }
        break;
    case EState::Ending:
        if (Input)
        {
            if (Input->IsKeyPressed(ALLEGRO_KEY_ENTER))
            {
                bReturnPressed = true;
            }
            if (bReturnPressed && Input->IsKeyReleased(ALLEGRO_KEY_ENTER))
            {
                bShouldEndGame = true;
            }
        }
        break;
    }
}

void GameFlow::OnShutdown()
{
    delete GameUI;
    GameUI = nullptr;

    delete Input;
    Input = nullptr;
}

void GameFlow::SetPlayerIsDead()
{
    CurrentState = EState::Ending;
    if (GameUI)
    {
        //GameUI->SetGameOver(CurrentScore);
    }
}

void GameFlow::UpdateLivesLeft(int NewLivesLeft)
{
    if (GameUI)
    {
        //GameUI->UpdateLivesLeft(NewLivesLeft);
    }
}

void GameFlow::AddScore(int ScoreToAdd)
{
    CurrentScore += ScoreToAdd;
    if (GameUI)
    {
        //GameUI->UpdateScore(CurrentScore);
    }
}

void GameFlow::AddObjectToDisableAtStart(GameObject* ObjectToDisable)
{
    ObjectsToDisableAtStart.push_back(ObjectToDisable);
}
