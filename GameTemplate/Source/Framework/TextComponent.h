#pragma once

#include "GameComponent.h"
#include <string>

using namespace std;

class TextComponent : public GameComponent
{
public:
    TextComponent(class GameObject* Owner);

    void SetText(string NewText) { Text = NewText; }
    void SetFont(string FontPath, int FontSize);
    void SetVisible(bool bIsNowVisible);
    bool IsVisible() const;

protected:
    virtual void OnRender() override;
    
private:
    string Text;
    bool bIsVisible = true;
    ALLEGRO_FONT* Font = nullptr;
};

