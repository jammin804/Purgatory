# Importing other files
import Globals

# Entry point for most programs
def Main(): 
    # Game Framework Initialises
    if (Globals.MyGameFramework.Init() == False):
        return
    
    # Game Framework keeps updating until it returns False
    while (Globals.MyGameFramework.Update() == True):
        continue
    
    # Game Framework shuts down
    Globals.MyGameFramework.Shutdown()

# Call the Main function    
Main()