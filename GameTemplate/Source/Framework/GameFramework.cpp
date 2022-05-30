#include "GameFramework.h"

#include "GameObject.h"
#include "InputComponent.h"
#include <algorithm>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include "BoxCollisionComponent.h"

GameFramework* GameFramework::Instance = nullptr;

const int Globals::WindowSizeX = 1280;
const int Globals::WindowSizeY = 720;

//////////////////////////////////////////////////////////////////////////
GameFramework::GameFramework()
{
}

//////////////////////////////////////////////////////////////////////////
GameFramework::~GameFramework()
{
    al_destroy_display(Display);
    al_destroy_timer(Timer);
    al_destroy_event_queue(EventQueue);
}

void GameFramework::DestroyObject(void*& Object, size_t SizeOfObject)
{
    if (Instance)
    {
        if (Object)
        {
            Instance->MemManager.Free(Object, SizeOfObject);
            Object = nullptr;
        }
    }
}

bool GameFramework::InitInternal()
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return false;
    }

    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return false;
    }

    Timer = al_create_timer(1.0 / 120.0);
    if (!Timer)
    {
        printf("couldn't initialize timer\n");
        return false;
    }

    EventQueue = al_create_event_queue();
    if (!EventQueue)
    {
        printf("couldn't initialize queue\n");
        return false;
    }

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    Display = al_create_display(Globals::WindowSizeX, Globals::WindowSizeY);
    if (!Display)
    {
        printf("couldn't initialize display\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
        printf("couldn't initialize primitives addon\n");
        return false;
    }

    if (!al_install_audio())
    {
        printf("couldn't initialize audio addon\n");
        return false;
    }

    if (!al_init_acodec_addon())
    {
        printf("couldn't initialize audio codec addon\n");
        return false;
    }

    if (!al_init_font_addon())
    {
        printf("couldn't initialize font addon\n");
        return false;
    }

    if (!al_init_ttf_addon())
    {
        printf("couldn't initialize ttf addon\n");
        return false;
    }

    if (!al_reserve_samples(16))
    {
        printf("couldn't reserve audio samples\n");
        return false;
    }

    FntManager.Init();

    GameObjects.reserve(512);
    InputComponents.reserve(4);

    OnInit();

    for (int i = 0; i < GameObjects.size(); ++i)
    {
        GameObject* GO = GameObjects[i];
        if (!GO->bInitialised)
        {
            GO->Init();
        }
    }

    OnPostInit();

    for (int i = 0; i < GameObjects.size(); ++i)
    {
        GameObject* GO = GameObjects[i];
        if (!GO->bFullyInitialised)
        {
            GO->PostInit();
        }
    }

    al_register_event_source(EventQueue, al_get_keyboard_event_source());
    al_register_event_source(EventQueue, al_get_display_event_source(Display));
    al_register_event_source(EventQueue, al_get_timer_event_source(Timer));

    al_start_timer(Timer);

    return true;
}

void GameFramework::RegisterGameObject(GameObject* NewGameObject)
{
    if (Instance && NewGameObject)
    {
        if (Instance->GameObjects.size() == 512)
        {
            assert(0);
        }
        Instance->GameObjects.push_back(NewGameObject);
    }
}

void GameFramework::RegisterInputComponent(InputComponent* NewInputComponent)
{
    if (Instance && NewInputComponent)
    {
        Instance->InputComponents.push_back(NewInputComponent);
    }
}

bool GameFramework::Update()
{
    return Instance->UpdateInternal();
}

bool GameFramework::UpdateInternal()
{
    static ALLEGRO_EVENT Event;
    al_wait_for_event(EventQueue, &Event);

    bool redraw = false;

    switch (Event.type)
    {
    case ALLEGRO_EVENT_TIMER:   
        {
            if (bIsGameOver)
            {
                return false;
            }

            float DeltaTime = al_get_time() - TimeOfLastUpdate;
            TimeOfLastUpdate = al_get_time();

            for (int i = 0; i < GameObjects.size(); ++i)
            {
                GameObject* GO = GameObjects[i];
                if (!GO->bInitialised)
                {
                    GO->Init();
                }
            }

            for (int i = 0; i < GameObjects.size(); ++i)
            {
                GameObject* GO = GameObjects[i];
                if (!GO->bFullyInitialised)
                {
                    GO->PostInit();
                }
            }

            OnUpdate(DeltaTime);

            for (auto GOIter = GameObjects.begin(); GOIter != GameObjects.end(); ++GOIter)
            {
                static bool bDeletedSomething = false;
                bDeletedSomething = false;
                GameObject* GO = (*GOIter);
                if (GO->bShouldDestroy)
                {
                    GO->Shutdown();
                    GO->bIsDestroyed = true;
                    void* GOMem = static_cast<void*>(GO);
                    DestroyObject(GOMem, sizeof(*GO));

                    GameObjects.erase(GOIter--);
                    continue;
                }

                if (GO->IsEnabled())
                {
                    if(GameComponent * Component = GO->GetComponent(ComponentType::BoxCollisionComponent))
                    {
                        BoxCollisionComponent* BoxCollision = static_cast<BoxCollisionComponent*>(Component);
						for (auto OtherGOIter = GameObjects.begin(); OtherGOIter != GameObjects.end(); ++OtherGOIter)
						{
							GameObject* OtherGO = (*OtherGOIter);
							if (OtherGO->IsEnabled())
							{
                                if (GameComponent* OtherComponent = OtherGO->GetComponent(ComponentType::BoxCollisionComponent))
                                {
                                    BoxCollisionComponent* OtherBoxCollision = static_cast<BoxCollisionComponent*>(OtherComponent);
                                    if (BoxCollision->DoesCollide(OtherBoxCollision))
                                    {
                                        GO->OnCollision(OtherGO);
                                        OtherGO->OnCollision(GO);
                                    }
                                }
							}
						}
                    }
                   
                    (GO)->Update(DeltaTime);
                }
            }
        
            redraw = true;
        }
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        for (InputComponent* InputComp : InputComponents)
        {
            InputComp->OnKeyPressed(Event.keyboard.keycode);
        }
        break;
    case ALLEGRO_EVENT_KEY_UP:
        for (InputComponent* InputComp : InputComponents)
        {
            InputComp->OnKeyReleased(Event.keyboard.keycode);
        }
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return false;
    }

    if (redraw && al_is_event_queue_empty(EventQueue))
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        vector<GameObject*> GameObjectsToRender;
        GameObjectsToRender.reserve(32);

        for (GameObject* GO : GameObjects)
        {
            if (GO->IsEnabled())
            {
                GameObjectsToRender.push_back(GO);
                
            }
        }

        std::sort(GameObjectsToRender.begin(), GameObjectsToRender.end(), [](GameObject* a, GameObject* b){
            if (a && b)
            {
                return a->GetRenderDepth() < b->GetRenderDepth();
            }
            return false;
        });

        for (GameObject* GO : GameObjectsToRender)
        {
            GO->Render();
        }

        al_flip_display();

        redraw = false;
    }

    return true;
}

void GameFramework::ShutdownInternal()
{
    FntManager.Shutdown();

    for (GameObject* GO : GameObjects)
    {
        GO->Shutdown();
    }
}

void GameFramework::Shutdown()
{
    delete Instance;
    Instance = nullptr;
}
