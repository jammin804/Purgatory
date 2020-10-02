import Framework.GameComponent
import pygame

class SoundComponent(Framework.GameComponent.GameComponent):
    def __init__(self, Owner):
        super().__init__(Owner)
        self.bIsLooped = False
        self.bIsPlaying = False
    
    def OnShutdown(self):
        if (self.AudioSample is not None):
            self.Stop()
    
    def LoadSample(self, SamplePath):
        self.AudioSample = pygame.mixer.Sound(SamplePath)
    
    def Play(self):
        self.AudioSample.play(-1 if self.bIsLooped else 0)
        self.bIsPlaying = True
    
    def Stop(self):
        self.AudioSample.stop()
        self.bIsPlaying = False
    
    def SetLooped(self, bIsLooping):
        self.bIsLooped = bIsLooping
    
    def SetVolume(self, NewVolume):
        self.AudioSample.set_volume(NewVolume)
    
    def IsPlaying(self):
        return self.bIsPlaying 
