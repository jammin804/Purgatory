import Globals

class GameObject(object):    
    def __init__(self):
        Globals.MyGameFramework.RegisterGameObject(self)
        self.Position = [0.0,0.0]
        self.Rotation = 0.0
        self.GameComponents = []
        self.bEnabled = True
        self.bInitialised = False
        self.bIsDestroyed = False
        self.RenderDepth = 0.0 #Higher values will be rendered on top
        
    def Destroy(self):
        Globals.MyGameFramework.UnregisterGameObject(self)
        self.bIsDestroyed = True
  
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
        self.bInitialised = True
    
    def _Update_(self, DeltaTime):
        if not self.bInitialised:
            return
        self.OnUpdate(DeltaTime)
        for Component in self.GameComponents:
            Component._Update_(DeltaTime)
            
    def _Render_(self, Screen):
        for Component in self.GameComponents:
            Component._Render_(Screen)
            
    def _Shutdown_(self):
        for Component in self.GameComponents:
            Component._Shutdown_()
            self.GameComponents.remove(Component)
        self.OnShutdown()

    def RegisterComponent(self, NewComponent):
        self.GameComponents.append(NewComponent)
