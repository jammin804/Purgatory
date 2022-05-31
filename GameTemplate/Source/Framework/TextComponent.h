#pragma once

#include "GameComponent.h"
#include "EString.h"

class TextComponent : public GameComponent
{
public:
    TextComponent(class GameObject* Owner);

    void SetText(EString NewText) { Text = NewText; }
    void SetFont(EString FontPath, int FontSize);
    void SetVisible(bool bIsNowVisible);
    bool IsVisible() const;

protected:
    virtual void OnRender() override;
    
private:
    EString Text;
    bool bIsVisible = true;
    ALLEGRO_FONT* Font = nullptr;
};

