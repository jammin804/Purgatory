#include "TextComponent.h"
#include "allegro5/allegro_font.h"
#include "Globals.h"
#include "GameObject.h"


TextComponent::TextComponent(class GameObject* Owner)
    : GameComponent(Owner){}

void TextComponent::OnInit()
{
    
}

void TextComponent::OnUpdate()
{

}

void TextComponent::OnRender()
{
    const GameObject* Owner = GetOwner();
    al_draw_text(Globals::DefaultFont, al_map_rgb(255, 255, 255), Owner->GetPosX() + GetOffsetX(), Owner->GetPosY() + GetOffsetY(), 0, Text.c_str());
}
