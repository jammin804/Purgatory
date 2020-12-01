#include "InputComponent.h"
#include "GameObject.h"
#include "GameFramework.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2
#define KEY_PRESSED  3

InputComponent::InputComponent(class GameObject* Owner)
    : GameComponent(Owner)
{
    GameFramework::RegisterInputComponent(this);
}


bool InputComponent::IsKeyPressed(int KeyCode) const
{
    return Keys[KeyCode] & KEY_PRESSED;
}

bool InputComponent::IsKeyReleased(int KeyCode) const
{
    return Keys[KeyCode] & KEY_RELEASED;
}

bool InputComponent::IsKeyJustPressed(int KeyCode) const
{
	return Keys[KeyCode] & (KEY_PRESSED & KEY_SEEN);
}

void InputComponent::OnKeyPressed(int Keycode)
{
    Keys[Keycode] = KEY_SEEN | KEY_RELEASED;
}

void InputComponent::OnKeyReleased(int Keycode)
{
    Keys[Keycode] &= KEY_RELEASED;
}

void InputComponent::OnUpdate(float DeltaTime)
{
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
        Keys[i] &= KEY_SEEN;
}