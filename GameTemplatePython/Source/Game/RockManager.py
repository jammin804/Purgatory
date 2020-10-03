import Framework.GameObject
import Game.Rock
import pygame
import math
import random
import Globals

class RockManager(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.Rocks = []
        self.SpawnTimer = 2.0
        self.TimeSinceSpawn = 10.0
        
    def CreateRock(self):
        Rock = Game.Rock.Rock()
        Rock.Position = [random.randrange(0, Globals.ScreenSize[0]), random.randrange(0, Globals.ScreenSize[1])]
        self.Rocks.append(Rock)
        
    def OnUpdate(self, DeltaTime):      
        
        for Rock in self.Rocks:
            if (Rock.bIsDestroyed):
                self.Rocks.remove(Rock)
         
        self.TimeSinceSpawn += DeltaTime
        if self.TimeSinceSpawn > self.SpawnTimer:
            self.SpawnTimer *= 0.999
            self.TimeSinceSpawn = 0.0
            self.CreateRock()