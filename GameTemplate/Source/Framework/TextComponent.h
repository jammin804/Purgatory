#pragma once

#include "GameComponent.h"
#include <string>

using namespace std;

class TextComponent : public GameComponent
{
public:
    TextComponent(class GameObject* Owner);

    void SetText(string NewText) { Text = NewText; }

protected:
    virtual void OnRender() override;
    
private:
    string Text;
};

