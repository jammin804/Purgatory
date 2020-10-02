import Globals

def Main(): 
    if (Globals.MyGameFramework.Init() == False):
        return
    
    while (Globals.MyGameFramework.Update()):
        continue
    
    Globals.MyGameFramework.Shutdown()
    
Main()