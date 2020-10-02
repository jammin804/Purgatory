#include "GameFramework.h"

import pygame
#include "GameObject.h"
#include "InputComponent.h"

ColorBlue = 0, 0, 100

class GameFramework(object):

    def __init__(self, ScreenSize, TargetFPS):
        self.ScreenSize = ScreenSize
        self.TargetFPS = TargetFPS

    GameObjects = []

    def RegisterGameObject(self, NewGameObject):
        self.GameObjects.append(NewGameObject)
    
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
        self.FPSClock = pygame.time.Clock()
        self.Screen = pygame.display.set_mode(self.ScreenSize)
        
        self.OnInit()
        for GameObject in self.GameObjects:
            GameObject._Init_()
            GameObject._PostInit_()

        self.OnPostInit()

        #register things here

        return True

    def Update(self):
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                return False
            elif event.type == pygame.KEYDOWN:
                pass
            elif event.type == pygame.KEYUP:
                pass
        
        self.OnUpdate(self.GetTimeElapsed())
        for GameObject in self.GameObjects:
            GameObject._Update_(self.GetTimeElapsed())
        # case ALLEGRO_EVENT_KEY_DOWN:
        #     for (InputComponent* InputComp : InputComponents)
        #     {
        #         InputComp->OnKeyPressed(Event.keyboard.keycode);
        #     }
        #     break;
        # case ALLEGRO_EVENT_KEY_UP:
        #     for (InputComponent* InputComp : InputComponents)
        #     {
        #         InputComp->OnKeyReleased(Event.keyboard.keycode);
        #     }
        #     break;
        
        self.Screen.fill(ColorBlue)
        
        for GameObject in self.GameObjects:
            GameObject._Render_(self.Screen)
        
        pygame.display.update()
        self.FPSClock.tick(self.TargetFPS)
        # TODO Flip Display

        return True
    
    def Shutdown(self):
        self.OnShutdown()
        for GameObject in self.GameObjects:
            GameObject._Shutdown_()


# private:
#     static void RegisterGameObject(GameObject* NewGameObject);
#     static void RegisterInputComponent(InputComponent* NewInputComponent);

#     bool InitInternal();
#     bool UpdateInternal();
#     void ShutdownInternal();

# protected:
#     float WindowSizeX = 1280;
#     float WindowSizeY = 720;

# private:

#     vector<GameObject*> GameObjects;
#     vector<InputComponent*> InputComponents;

#     static GameFramework* Instance;

#     struct ALLEGRO_TIMER* Timer;
#     struct ALLEGRO_EVENT_QUEUE* EventQueue;
#     struct ALLEGRO_DISPLAY* Display;
# };

# bool GameFramework::InitInternal()
# {
#     if (!al_init())
#     {
#         printf("couldn't initialize allegro\n");
#         return false;
#     }

#     if (!al_install_keyboard())
#     {
#         printf("couldn't initialize keyboard\n");
#         return false;
#     }

#     Timer = al_create_timer(1.0 / 30.0);
#     if (!Timer)
#     {
#         printf("couldn't initialize timer\n");
#         return false;
#     }

#     EventQueue = al_create_event_queue();
#     if (!EventQueue)
#     {
#         printf("couldn't initialize queue\n");
#         return false;
#     }

#     Display = al_create_display(WindowSizeX, WindowSizeY);
#     if (!Display)
#     {
#         printf("couldn't initialize display\n");
#         return false;
#     }

#     if (!al_init_image_addon())
#     {
#         printf("couldn't initialize image addon\n");
#         return false;
#     }

#     if (!al_install_audio())
#     {
#         printf("couldn't initialize audio addon\n");
#         return false;
#     }

#     if (!al_init_acodec_addon())
#     {
#         printf("couldn't initialize audio codec addon\n");
#         return false;
#     }

#     if (!al_reserve_samples(16))
#     {
#         printf("couldn't reserve audio samples\n");
#         return false;
#     }

#     GameObjects.reserve(32);
#     InputComponents.reserve(4);

#     OnInit();

#     for (GameObject* GO : GameObjects)
#     {
#         GO->Init();
#         GO->PostInit();
#     }

#     OnPostInit();

#     al_register_event_source(EventQueue, al_get_keyboard_event_source());
#     al_register_event_source(EventQueue, al_get_display_event_source(Display));
#     al_register_event_source(EventQueue, al_get_timer_event_source(Timer));

#     al_start_timer(Timer);

#     return true;
# }

# void GameFramework::RegisterGameObject(GameObject* NewGameObject)
# {
#     if (Instance && NewGameObject)
#     {
#         Instance->GameObjects.push_back(NewGameObject);
#     }
# }

# void GameFramework::RegisterInputComponent(InputComponent* NewInputComponent)
# {
#     if (Instance && NewInputComponent)
#     {
#         Instance->InputComponents.push_back(NewInputComponent);
#     }
# }

# bool GameFramework::Update()
# {
#     return Instance->UpdateInternal();
# }

# bool GameFramework::UpdateInternal()
# {
#     static ALLEGRO_EVENT Event;
#     al_wait_for_event(EventQueue, &Event);

#     bool redraw = false;

#     switch (Event.type)
#     {
#     case ALLEGRO_EVENT_TIMER:
#         OnUpdate();
#         for (GameObject* GO : GameObjects)
#         {
#             GO->Update();
#         }
#         redraw = true;
#         break;

#     case ALLEGRO_EVENT_KEY_DOWN:
#         for (InputComponent* InputComp : InputComponents)
#         {
#             InputComp->OnKeyPressed(Event.keyboard.keycode);
#         }
#         break;
#     case ALLEGRO_EVENT_KEY_UP:
#         for (InputComponent* InputComp : InputComponents)
#         {
#             InputComp->OnKeyReleased(Event.keyboard.keycode);
#         }
#         break;

#     case ALLEGRO_EVENT_DISPLAY_CLOSE:
#         return false;
#     }

#     if (redraw && al_is_event_queue_empty(EventQueue))
#     {
#         al_clear_to_color(al_map_rgb(0, 0, 0));
#         for (GameObject* GO : GameObjects)
#         {
#             GO->Render();
#         }
#         al_flip_display();

#         redraw = false;
#     }

#     return true;
# }

# void GameFramework::ShutdownInternal()
# {
#     for (GameObject* GO : GameObjects)
#     {
#         GO->Shutdown();
#     }
# }

# void GameFramework::Shutdown()
# {
#     al_destroy_font(Globals::DefaultFont);

#     delete Instance;
#     Instance = nullptr;
# }