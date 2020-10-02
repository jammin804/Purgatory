import Globals
import Game.Player
import Game.Rock
import Game.Background
import Game.UIText
import Framework.GameFramework
import pygame

class Asteroids(Framework.GameFramework.GameFramework):
    def __init__(self, ScreenSize, TargetFPS):
        super().__init__(ScreenSize, TargetFPS)
        self.CurrentScore = 0
    
    
    def OnInit(self):
        pygame.display.set_caption('Asteroids Game')
        Globals.DefaultFont = pygame.font.Font('Font/arial.ttf', 32)
        self.BG = Game.Background.Background()
        self.Player1 = Game.Player.Player()
        self.Rock = Game.Rock.Rock()
        self.UI = Game.UIText.UIText()
        
    def OnPostInit(self):
        print("On Post Init")
        
    def OnUpdate(self, DeltaTime):
        if self.Player1.Collision.DoesCollide(self.Rock.Collision):
            self.Player1.bEnabled = False
        #print("On Update")
        
    def OnShutdown(self):
        print("On Shutdown")
