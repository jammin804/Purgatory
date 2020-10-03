import Globals
import Game.Player
import Game.RockManager
import Game.Explosion
import Game.Background
import Game.GameFlow
import Framework.GameFramework
import pygame
import copy

class Asteroids(Framework.GameFramework.GameFramework):
    def __init__(self, ScreenSize, TargetFPS):
        super().__init__(ScreenSize, TargetFPS)
    
    def OnInit(self):
        pygame.display.set_caption('Asteroids Game')
        Globals.DefaultFont = pygame.font.Font('Font/arial.ttf', 32)
        self.BG = Game.Background.Background()
        self.Player1 = Game.Player.Player()
        self.RockManager = Game.RockManager.RockManager()
        self.GameFlow = Game.GameFlow.GameFlow()
        self.GameFlow.ObjectsToDisableAtStart.append(self.Player1)
        self.GameFlow.ObjectsToDisableAtStart.append(self.RockManager)
        
    def OnPostInit(self):
        pass
        
    def OnUpdate(self, DeltaTime):         
        
        if self.GameFlow.bEndGame:
            self.GameOver = True
            return
           
        for Rock in self.RockManager.Rocks:
            if not self.Player1.bInvulnerable and Rock is not None:
                if self.Player1.Collision.DoesCollide(Rock.Collision):
                    Explosion = Game.Explosion.Explosion()
                    Explosion.Scale = 1.0
                    Explosion.Position = self.Player1.Position
                    if (self.Player1.HandleDeath()):
                        self.GameFlow.SetPlayerDied()
                    else:
                        self.GameFlow.UpdateLivesLeft(self.Player1.LivesLeft)
            for Laser in self.Player1.Lasers: 
                if Rock.Collision.DoesCollide(Laser.Collision):
                    self.GameFlow.AddScore(5 * (Rock.SplitsLeft + 1))
                    Explosion = Game.Explosion.Explosion()
                    Explosion.Scale = Rock.RockImage.Scale
                    Explosion.Position = copy.copy(Rock.Position)
                    if (Rock.SplitsLeft == 0):
                        Rock.Destroy()
                    else:
                        Rock.bNeedsSplit = True
                    Laser.Destroy()
                    break
        
    def OnShutdown(self):
        pass
