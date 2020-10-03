import pygame

ColorBlue = 0, 0, 100

class GameFramework(object):

    def __init__(self, ScreenSize, TargetFPS):
        self.ScreenSize = ScreenSize
        self.TargetFPS = TargetFPS
        self.GameOver = False

    GameObjects = []

    def RegisterGameObject(self, NewGameObject):
        self.GameObjects.append(NewGameObject)
    def UnregisterGameObject(self, GameObjectToUnregister):
        for GameObject in self.GameObjects:
            if GameObject == GameObjectToUnregister:
                GameObject._Shutdown_()
                self.GameObjects.remove(GameObject)
                break        
        
    
    def OnInit(self):
        pass
    def OnPostInit(self):
        pass
    def OnUpdate(self, DeltaTime):
        pass
    def OnShutdown(self):
        pass
    
    def GetTimeElapsed(self):
        return self.FPSClock.get_time() * 0.001
    
    def Init(self):
        pygame.init()
        pygame.mixer.pre_init(frequency=44100, size=-16, channels=1, buffer=512)
        pygame.mixer.init()
        self.FPSClock = pygame.time.Clock()
        self.Screen = pygame.display.set_mode(self.ScreenSize)
        
        self.OnInit()
        self.OnPostInit()

        return True

    def GameObjectRenderSort(self, GameObject):
        return GameObject.RenderDepth

    def Update(self):
    
        if (self.GameOver):
            return False
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                return False
            elif event.type == pygame.KEYDOWN:
                pass
            elif event.type == pygame.KEYUP:
                pass
            
        for GameObject in self.GameObjects:
            if not GameObject.bInitialised:
                GameObject._Init_()

        for GameObject in self.GameObjects:
            if not GameObject.bInitialised:                
                GameObject._PostInit_()
        
        self.OnUpdate(self.GetTimeElapsed())
        for GameObject in self.GameObjects:
            if GameObject.bEnabled:
                GameObject._Update_(self.GetTimeElapsed())
        
        self.Screen.fill(ColorBlue)
        
        for GameObject in sorted(self.GameObjects, key=self.GameObjectRenderSort):
            if GameObject.bEnabled:
                GameObject._Render_(self.Screen)
        
        pygame.display.update()
        self.FPSClock.tick(self.TargetFPS)

        return True
    
    def Shutdown(self):
        self.OnShutdown()
        for GameObject in self.GameObjects:
            GameObject._Shutdown_()