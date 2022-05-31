#include "FontManager.h"
#include <allegro5/allegro_ttf.h>

ALLEGRO_FONT* Globals::DefaultFont;

void FontManager::Init()
{
    Globals::DefaultFont = al_create_builtin_font();
    if (!Globals::DefaultFont)
    {
        printf("couldn't initialize default font\n");
    }
}

void FontManager::Shutdown()
{
    al_destroy_font(Globals::DefaultFont);
    for (auto KeyPair : FontMap)
    {
        al_destroy_font(KeyPair.second);
    }
    FontMap.clear();
}

ALLEGRO_FONT* FontManager::FindOrAddFont(EString FontPath, int Size)
{
    FontKey Key;
    Key.FontPath = FontPath;
    Key.FontSize = Size;

    auto iter = FontMap.find(Key);
    if (iter != FontMap.end())
    {
        return iter->second;
    }
    ALLEGRO_FONT* NewFont = al_load_ttf_font(FontPath.c_str(), Size, 0);
    if (NewFont)
    {
        FontMap.insert(pair<FontKey, ALLEGRO_FONT*>(Key, NewFont));
    }
    return NewFont;
}

