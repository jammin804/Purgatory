import Globals

class GameObject(object):    
    def __init__(self):
        Globals.MyGameFramework.RegisterGameObject(self)
        self.Position = [0.0,0.0]
        self.Rotation = 0.0
        self.GameComponents = []
  
    def OnInit(self):
        pass
    
    def OnPostInit(self):
        pass
    
    def OnUpdate(self, DeltaTime):
        pass
    
    def OnShutdown(self):
        pass

    def _Init_(self):
        self.OnInit()
        for Component in self.GameComponents:
            Component._Init_()
    
    def _PostInit_(self):
        self.OnPostInit()
    
    def _Update_(self, DeltaTime):
        self.OnUpdate(DeltaTime)
        for Component in self.GameComponents:
            Component._Update_(DeltaTime)
            
    def _Render_(self, Screen):
        for Component in self.GameComponents:
            Component._Render_(Screen)
            
    def _Shutdown_(self):
        for Component in self.GameComponents:
            Component._Shutdown_()
        self.OnShutdown()

    def RegisterComponent(self, NewComponent):
        self.GameComponents.append(NewComponent)
