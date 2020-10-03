import Framework.GameObject

class GameComponent(object):
    def __init__(self, Owner):
        self.Owner = Owner
        self.Owner.RegisterComponent(self)
        self.Offset = [0,0]

    def OnInit(self):
        pass

    def OnUpdate(self, DeltaTime):
        pass

    def OnRender(self, Screen):
        pass

    def OnShutdown(self):
        pass

    def GetOwner(self):
        return self.Owner

    def _Init_(self):
        self.OnInit()
        
    def _Update_(self, DeltaTime):
        self.OnUpdate(DeltaTime)
        
    def _Render_(self, Screen):
        self.OnRender(Screen)
        
    def _Shutdown_(self):
        self.OnShutdown()
