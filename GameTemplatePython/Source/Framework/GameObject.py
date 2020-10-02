import Globals

class GameObject(object):
    
    Position = [0.0,0.0]
    Rotation = 0.0
    GameComponents = []
    
    def __init__(self):
        Globals.MyGameFramework.RegisterGameObject(self)
  
    def OnInit(self):
        pass
    
    def OnPostInit(self):
        pass
    
    def OnUpdate(self):
        pass
    
    def OnShutdown(self):
        pass

    def _Init_(self):
        self.OnInit()
        for Component in self.GameComponents:
            Component._Init_()
    
    def _PostInit_(self):
        self.OnPostInit()
    
    def _Update_(self):
        self.OnUpdate()
        for Component in self.GameComponents:
            Component._Update_()
            
    def _Render_(self, Screen):
        for Component in self.GameComponents:
            Component._Render_(Screen)
            
    def _Shutdown_(self):
        for Component in self.GameComponents:
            Component._Shutdown_()
        self.OnShutdown()

    def RegisterComponent(self, NewComponent):
        self.GameComponents.append(NewComponent)
