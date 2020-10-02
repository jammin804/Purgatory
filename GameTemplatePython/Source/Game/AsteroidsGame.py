
#include "Framework/GameFramework.h"
import Globals
import Game.Player
import Framework.GameFramework
import pygame

#todo AsteroidsGame(GameFramework)
class Asteroids(Framework.GameFramework.GameFramework):
    def __init__(self, ScreenSize, TargetFPS):
        super().__init__(ScreenSize, TargetFPS)
    # PlayerScore = UIText()
    # Enemy1 = Enemy()
    # BG = Background()
    
    CurrentScore = 0
    
    def OnInit(self):
        pygame.display.set_caption('Asteroids Game')
        self.Player1 = Game.Player.Player()
        print("On Init")
        
    def OnPostInit(self):
        print("On Post Init")
        
    #     if (BG)
    # {
    #     BG->SetImage("Art/Background.png");
    #     //BG->SetMusic("Audio/Music.wav");
    #     BG->SetPosition(638.0f, 360.0f);
    # }

    # if (Player1)
    # {
    #     Player1->SetAvatarImage("Art/Ship.png");
    #     Player1->SetThrustersImage("Art/Thrusters.png");
    #     Player1->SetThrustersSound("Audio/Thruster.wav");
    #     Player1->SetPosition(638.0f, 360.0f);
    # }

    # if (Enemy1)
    # {
    #     Enemy1->SetAvatarImage("Art/Enemy.png");
    #     Enemy1->SetPosition(900.0f, 360.0f);
    # }

    # if (PlayerScore)
    # {
    #     PlayerScore->SetText("Player1: ");
    #     PlayerScore->SetPosition(100.0f, 100.0f);
    # }
        
    def OnUpdate(self, DeltaTime):
        pass
        #print("On Update")
        
    def OnShutdown(self):
        print("On Shutdown")
