#pragma once

#include <vector>
#include "Globals.h"
#include <allegro5/allegro_font.h>

using namespace std;

class GameObject;
class InputComponent;

class GameFramework
{
    friend class GameObject;
    friend class GameComponent;
    friend class InputComponent;

protected:
    GameFramework();
    virtual ~GameFramework();

public:
    template<typename T>
    static bool Init();

    static bool Update();

    static void Shutdown();

    static GameFramework& Get() { return *Instance; }

    virtual void OnInit(){}

    virtual void OnPostInit() {}

    virtual void OnUpdate(){}

    virtual void OnShutdown(){}


private:
    static void RegisterGameObject(GameObject* NewGameObject);
    static void RegisterInputComponent(InputComponent* NewInputComponent);

    bool InitInternal();
    bool UpdateInternal();
    void ShutdownInternal();

protected:
    float WindowSizeX = 1280;
    float WindowSizeY = 720;

private:

    vector<GameObject*> GameObjects;
    vector<InputComponent*> InputComponents;

    static GameFramework* Instance;

    struct ALLEGRO_TIMER* Timer;
    struct ALLEGRO_EVENT_QUEUE* EventQueue;
    struct ALLEGRO_DISPLAY* Display;
};

template<typename T>
bool GameFramework::Init()
{
    if (Instance)
    {
        return false;
    }

    Instance = new T();
    
    bool BaseInitResult = Instance->InitInternal();

    Globals::DefaultFont = al_create_builtin_font();
    if (!Globals::DefaultFont)
    {
        printf("couldn't initialize font\n");
        return false;
    }

    return BaseInitResult;
}