#include "InputComponent.h"
#include "GameObject.h"
#include "GameFramework.h"

#define KEY_SEEN     1
#define KEY_PRESSED  2

InputComponent::InputComponent(class GameObject* Owner)
    : GameComponent(Owner)
{
    GameFramework::RegisterInputComponent(this);
}


bool InputComponent::IsKeyPressed(int KeyCode) const
{
    int result = Keys[KeyCode] & KEY_PRESSED;
    return result != 0;
}

bool InputComponent::IsKeyReleased(int KeyCode) const
{
    int result = Keys[KeyCode] & KEY_PRESSED;
    return result == 0;
}

bool InputComponent::IsKeyJustPressed(int KeyCode) const
{
    return IsKeyPressed(KeyCode) && Keys[KeyCode] & KEY_SEEN;
}

bool InputComponent::IsKeyJustReleased(int KeyCode) const
{
    return IsKeyReleased(KeyCode) && Keys[KeyCode] & KEY_SEEN;
}

void InputComponent::OnKeyPressed(int KeyCode)
{
    Keys[KeyCode] |= KEY_PRESSED;
    Keys[KeyCode] |= KEY_SEEN;
}

void InputComponent::OnKeyReleased(int KeyCode)
{
    Keys[KeyCode] &= ~KEY_PRESSED;
    Keys[KeyCode] |= KEY_SEEN;
}

void InputComponent::OnUpdate(float DeltaTime)
{
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
    {
        Keys[i] &= ~KEY_SEEN;
    }        
}