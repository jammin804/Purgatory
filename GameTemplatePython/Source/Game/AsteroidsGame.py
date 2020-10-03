import Globals
import Game.Player
import Game.RockManager
import Game.Explosion
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
        self.RockManager = Game.RockManager.RockManager()
        self.UI = Game.UIText.UIText()
        
    def OnPostInit(self):
        pass
        
    def OnUpdate(self, DeltaTime):    
        for Rock in self.RockManager.Rocks:
            if self.Player1.bEnabled and Rock is not None:
                if self.Player1.Collision.DoesCollide(Rock.Collision):
                    Explosion = Game.Explosion.Explosion()
                    Explosion.Position = self.Player1.Position
                    self.Player1.bEnabled = False
            for Laser in self.Player1.Lasers: 
                if Rock.Collision.DoesCollide(Laser.Collision):
                    Explosion = Game.Explosion.Explosion()
                    Explosion.Position = Rock.Position
                    Rock.Destroy()
                    Laser.Destroy()
                    self.CurrentScore += 10
                    self.UI.UpdateScore(self.CurrentScore)
                    break
        
    def OnShutdown(self):
        pass
