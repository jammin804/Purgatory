#pragma once

#include "GameComponent.h"
#include <allegro5/keycodes.h>

using namespace std;

class InputComponent : public GameComponent
{
    friend class GameFramework;
public:
    InputComponent(class GameObject* Owner);

    bool IsKeyPressed(int KeyCode) const;
    bool IsKeyReleased(int KeyCode) const;

protected:
    virtual void OnUpdate(float DeltaTime) override;

private:
    void OnKeyPressed(int Keycode);
    void OnKeyReleased(int Keycode);

    unsigned char Keys[ALLEGRO_KEY_MAX];
};

