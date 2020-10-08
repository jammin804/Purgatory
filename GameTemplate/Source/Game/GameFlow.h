#pragma once

#include "Framework/GameObject.h"
#include <vector>

using namespace std;


class GameFlow : public GameObject
{
    enum class EState
    {
        Starting = 0,
        InGame,
        Ending
    };

    protected:
        virtual void OnInit() override;
        virtual void OnPostInit() override;
        virtual void OnUpdate(float DeltaTime) override;
        virtual void OnShutdown() override;

    public:
        void SetPlayerIsDead();
        void UpdateLivesLeft(int NewLivesLeft);
        void AddScore(int ScoreToAdd);
        void AddObjectToDisableAtStart(GameObject* ObjectToDisable);
        bool ShouldEndGame() const { return bShouldEndGame; }
    private:
        vector<GameObject*> ObjectsToDisableOutsideGame;
        int CurrentScore = 0;
        EState CurrentState = EState::Starting;
        class InputComponent* Input = nullptr;
        float TimeRemaining = 120.0f;
        class UIText* GameUI = nullptr;
        bool bReturnPressed = false;
        bool bShouldEndGame = false;
};

