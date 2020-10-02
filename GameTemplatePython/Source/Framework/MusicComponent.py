import Framework.GameComponent
import pygame

class MusicComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bIsLooped = False
        self.bIsPlaying = False
    
    def OnShutdown(self):
        self.Stop()
    
    def LoadSample(self, SamplePath):
        pygame.mixer.music.load(SamplePath)
    
    def Play(self):
        pygame.mixer.music.play(-1 if self.bIsLooped else 0)
        self.bIsPlaying = True
            
    
    def Stop(self):
        pygame.mixer.music.stop()
        self.bIsPlaying = False
    
    def SetLooped(self, bIsLooping):
        self.bIsLooped = bIsLooping
    
    def SetVolume(self, NewVolume):
        pygame.mixer.music.set_volume(NewVolume)
    
    def IsPlaying(self):
        return self.bIsPlaying  
