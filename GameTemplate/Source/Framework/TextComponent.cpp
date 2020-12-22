#include "TextComponent.h"
#include "allegro5/allegro_font.h"
#include "Globals.h"
#include "GameObject.h"
#include "GameFramework.h"

TextComponent::TextComponent(class GameObject* Owner)
    : GameComponent(Owner){}

void TextComponent::OnRender()
{
    if (IsVisible())
    {
        const GameObject* Owner = GetOwner();
        al_draw_text(Font ? Font : Globals::DefaultFont, 
            al_map_rgb(255, 255, 255), 
            Owner->GetPositionX() + GetOffsetX(), 
            Owner->GetPositionY() + GetOffsetY(), 
            ALLEGRO_ALIGN_CENTRE,
            Text.c_str());
    }
}

void TextComponent::SetFont(string FontPath, int FontSize)
{
    Font = GameFramework::Get().FntManager.FindOrAddFont(FontPath, FontSize);
}

void TextComponent::SetVisible(bool bIsNowVisible)
{
    bIsVisible = bIsNowVisible;
}

bool TextComponent::IsVisible() const
{
    return bIsVisible;
}
