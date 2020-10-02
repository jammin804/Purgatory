import Framework.GameObject

class GameComponent(object):
    def __init__(self, Owner):
        self.Owner = Owner
        self.Owner.RegisterComponent(self)
        self.OffsetX = 0.0
        self.OffsetY = 0.0

    def OnInit(self):
        print("Component Init")

    def OnUpdate(self):
        pass

    def OnRender(self, Screen):
        pass

    def OnShutdown(self):
        pass

    def GetOwner(self):
        return self.Owner

    def _Init_(self):
        self.OnInit()
        
    def _Update_(self):
        self.OnUpdate()
        
    def _Render_(self, Screen):
        self.OnRender(Screen)
        
    def _Shutdown_(self):
        self.OnShutdown()
