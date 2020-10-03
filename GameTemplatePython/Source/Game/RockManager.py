import Framework.GameObject
import Game.Rock
import pygame
import math
import random
import copy
import Globals

class RockManager(Framework.GameObject.GameObject):
    
    def OnInit(self):
        self.Rocks = []
        self.SpawnTimer = 3.0
        self.TimeSinceSpawn = 0.0
        
    def CreateRock(self, SplitsLeft):
        Rock = Game.Rock.Rock()
        Rock.bNeedsSplit = False
        Rock.SplitsLeft = SplitsLeft
        self.Rocks.append(Rock)
        return Rock
        
    def SetRandomPosition(self, Rock):
        OffscreenStart = random.randrange(0, 3)
        StartingPos = []
        StartingDirection = []
        if OffscreenStart == 0:
            StartingPos = [-100, random.randrange(0, Globals.ScreenSize[1])]
            DirectionY = 1.0 - (StartingPos[1] / (Globals.ScreenSize[1] * 0.5))
            StartingDirection = [0.6, DirectionY * 0.25] 
        elif OffscreenStart == 1:
            StartingPos = [random.randrange(0, Globals.ScreenSize[0]), -100]
            DirectionX = 1.0 - (StartingPos[0] / (Globals.ScreenSize[0] * 0.5))
            StartingDirection = [DirectionX * 0.4, 0.4]    
        elif OffscreenStart == 2:
            StartingPos = [Globals.ScreenSize[0] + 100, random.randrange(0, Globals.ScreenSize[1])]
            DirectionY = 1.0 - (StartingPos[1] / (Globals.ScreenSize[1] * 0.5))
            StartingDirection = [-0.6, DirectionY * 0.25]    
        else:
            StartingPos = [random.randrange(0, Globals.ScreenSize[0]), Globals.ScreenSize[1] + 100]
            DirectionX = 1.0 - (StartingPos[0] / (Globals.ScreenSize[0] * 0.5))
            StartingDirection = [DirectionX * 0.4, -0.4]   
        Rock.Position = StartingPos
        Rock.MovementDirection = StartingDirection  
        Rock.MovementSpeed = 150.0
        
    def OnUpdate(self, DeltaTime):      
        
        for Rock in self.Rocks:
            if Rock.bNeedsSplit:
                Rock.Split()
                NewRock = self.CreateRock(Rock.SplitsLeft)
                NewRock.Position = copy.copy(Rock.Position)
                NewRock.MovementSpeed = copy.copy(Rock.MovementSpeed)
                NewRock.MovementDirection = copy.copy(Rock.MovementDirection)
                NewRock.MovementDirection[0] = -NewRock.MovementDirection[0]
                NewRock.MovementDirection[1] = -NewRock.MovementDirection[1]
            elif (Rock.bIsDestroyed):
                self.Rocks.remove(Rock)
         
        self.TimeSinceSpawn += DeltaTime
        if self.TimeSinceSpawn > self.SpawnTimer:
            self.SpawnTimer *= 0.979
            self.TimeSinceSpawn = 0.0
            NewRock = self.CreateRock(2)
            self.SetRandomPosition(NewRock)
            