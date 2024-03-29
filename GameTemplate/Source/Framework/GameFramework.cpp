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
#include "vcruntime_typeinfo.h"
#include "thread"

GameFramework* GameFramework::Instance = nullptr;

const int Globals::WindowSizeX = 1280;
const int Globals::WindowSizeY = 720;
const double Globals::FrameRate = 120.0;


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

    Timer = al_create_timer(1.0 / Globals::FrameRate);
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

    BmpManager.Init();
    GetFontManager().Init();

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

int GameFramework::RegisterCollisionComponent(BoxCollisionComponent* NewCollisionComponent)
{
    if (Instance && NewCollisionComponent)
    {
        Instance->CollisionComponents.push_back(NewCollisionComponent);
        return static_cast<int>(Instance->CollisionComponents.size()) - 1;
    }
    return -1;
}

void GameFramework::UnregisterCollisionComponent(int Index)
{
    if (Instance)
    {
        auto iter = Instance->CollisionComponents.begin() + Index;
        iter = Instance->CollisionComponents.erase(iter);
        for (; iter != Instance->CollisionComponents.end(); ++iter)
        {
            (*iter)->CollisionIndex = Index++;
        }
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

            for (auto GOIter = GameObjects.begin(); GOIter != GameObjects.end(); ++GOIter)
            {
                GameObject* GO = (*GOIter);
                if (GO->bShouldDestroy)
                {
                    GO->Shutdown();
                    GO->bIsDestroyed = true;
                    continue;
                }

                if (GO->IsEnabled())
                {                   
                    (GO)->Update(DeltaTime);
                }
            }

            for (auto CollisionIter = CollisionComponents.begin(); CollisionIter != CollisionComponents.end(); ++CollisionIter)
            {
                BoxCollisionComponent* BoxCollision = *CollisionIter;
                GameObject* Owner = BoxCollision->GetOwnerPrivate();
                if (!Owner->IsEnabled())
                {
                    continue;
                }

                for (auto OtherCollisionIter = CollisionIter + 1; OtherCollisionIter != CollisionComponents.end(); ++OtherCollisionIter)
                {
                    BoxCollisionComponent* OtherBoxCollision = *OtherCollisionIter;
                    GameObject* OtherOwner = OtherBoxCollision->GetOwnerPrivate();
                    if (!OtherOwner->IsEnabled())
                    {
                        continue;
                    }

                    if (BoxCollision->DoesCollide(OtherBoxCollision))
                    {
                        Owner->OnCollision(OtherOwner);
                        OtherOwner->OnCollision(Owner);
                    }
                }
            }

            for (auto GOIter = GameObjects.begin(); GOIter != GameObjects.end(); ++GOIter)
            {
                GameObject* GO = (*GOIter);
                if (GO->bIsDestroyed)
                {
					DestroyObject<GameObject>(GO);

					GameObjects.erase(GOIter--);
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
        GameObjectsToRender.reserve(GameObjects.size());

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

        bool bMultiThread = false;
        vector<std::thread> threads;
        if (bMultiThread)
        {
            threads.reserve(GameObjectsToRender.size());
        }
        for (GameObject* GO : GameObjectsToRender)
        {
            if (bMultiThread)
            {
                auto threadOperation = [GO]() {GO->Render(); };
                threads.push_back(std::thread (threadOperation));
            }
            else
            {
                GO->Render();
            }
        }
        if (bMultiThread)
        {
			for (std::thread& thread : threads)
			{
				thread.join();
			}
        }


        al_flip_display();

        redraw = false;
    }

    return true;
}

void GameFramework::ShutdownInternal()
{
    BmpManager.Shutdown();
    GetFontManager().Shutdown();

    for (GameObject* GO : GameObjects)
    {
        GO->Shutdown();
    }
}

void GameFramework::Shutdown()
{
    if (Instance)
    {
        Instance->ShutdownInternal();
    }

    delete Instance;
    Instance = nullptr;
}

void GameFramework::SetWindowTitle(const char* title)
{
    al_set_window_title(Display, title);
}
