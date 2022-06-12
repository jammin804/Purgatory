#pragma once

#include <vector>
#include "Globals.h"
#include "MemoryManager.h"
#include "FontManager.h"
#include "BitmapManager.h"
#include <new>

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

    virtual void OnShutdown(){}

    void SetGameOver() { bIsGameOver = true;}

    FontManager& GetFontManager() { return FntManager; }
    BitmapManager& GetBitmapManager() { return BmpManager; }

private:
    static void RegisterGameObject(GameObject* NewGameObject);
    static void RegisterInputComponent(InputComponent* NewInputComponent);

    template<typename T, class C>
    static T* CreateObjectOneArg(C* OneArgument);

    template<typename T>
    static T* CreateObject();

    template<typename T>
    static void DestroyObject(T*& Object);

    bool InitInternal();
    bool UpdateInternal();
    void ShutdownInternal();

private:

    vector<GameObject*> GameObjects;
    vector<InputComponent*> InputComponents;

    static GameFramework* Instance;

    struct ALLEGRO_TIMER* Timer;
    struct ALLEGRO_EVENT_QUEUE* EventQueue;
    struct ALLEGRO_DISPLAY* Display;

    FontManager FntManager;
    BitmapManager BmpManager;

    double TimeOfLastUpdate = 0.0;

    bool bIsGameOver = false;
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

    return BaseInitResult;
}

template<typename T>
T* GameFramework::CreateObject()
{
    if (Instance)
    {
        void* MemBlock = MemManager.Allocate(sizeof(T));
        memset(MemBlock, 0, sizeof(T));
        return new (MemBlock) T;
    }
    return nullptr;
}

template<typename T, class C>
T* GameFramework::CreateObjectOneArg(C* OneArgument)
{
    if (Instance)
    {
        void* MemBlock = MemManager.Allocate(sizeof(T));
        memset(MemBlock, 0, sizeof(T));
        return new (MemBlock) T(OneArgument);
    }
    return nullptr;
}

template<typename T>
void GameFramework::DestroyObject(T*& Object)
{
    if (Instance)
    {
        if (Object)
        {
            MemManager.Free(Object, Object->memsize);
            Object = nullptr;
        }
    }
}
