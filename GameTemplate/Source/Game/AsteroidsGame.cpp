#include "AsteroidsGame.h"

#include "Background.h"
#include "Player.h"
#include "UIText.h"
#include <sstream>

void AsteroidsGame::OnInit()
{
    BG = new Background();
    Player1 = new Player();
    PlayerScore = new UIText();
}

void AsteroidsGame::OnPostInit()
{
    if (BG)
    {
        BG->SetImage("Art/Background.png");
        BG->SetMusic("Audio/Music.wav");
        BG->SetPos(638.0f, 360.0f);
    }

    if (Player1)
    {
        Player1->SetAvatarImage("Art/Ship.png");
        Player1->SetThrustersImage("Art/Thrusters.png");
        Player1->SetThrustersSound("Audio/Thruster.wav");
        Player1->SetPos(100.0f, 100.0f);
    }

    if (PlayerScore)
    {
        PlayerScore->SetText("Player1: ");
        PlayerScore->SetPos(100.0f, 100.0f);
    }
}

void AsteroidsGame::OnUpdate()
{
    
}
