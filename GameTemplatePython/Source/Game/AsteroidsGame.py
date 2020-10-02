import Globals
import Game.Player
import Game.Rock
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
        self.Rock = Game.Rock.Rock()
        self.UI = Game.UIText.UIText()
        self.Explosion = None
        
    def OnPostInit(self):
        pass
        
    def OnUpdate(self, DeltaTime):
        if self.Explosion is not None:
            if self.Explosion.IsFinished():
                self.Explosion.Destroy()
                self.Explosion = None
        
        if self.Player1 is not None:
            if self.Player1.Collision.DoesCollide(self.Rock.Collision):
                self.Explosion = Game.Explosion.Explosion()
                self.Explosion.Position = self.Player1.Position
                self.Player1.Destroy()
                self.Player1 = None
        #print("On Update")
        
    def OnShutdown(self):
        pass
