#pragma once

#include <allegro5/allegro_font.h>
#include <string>
#include <map>

using namespace std;


namespace Globals
{
    extern ALLEGRO_FONT* DefaultFont;
};

struct FontKey
{
    string FontPath;
    int FontSize;
    
    bool operator==(FontKey& Other) const
    {
        return FontPath == Other.FontPath &&
            FontSize == Other.FontSize;
    }

    bool operator<(const FontKey& Other) const 
    {
        return FontPath != Other.FontPath ||
            FontSize < Other.FontSize;
    }
};

class FontManager
{
    friend class GameFramework;
    void Init();
    void Shutdown();
public:
    ALLEGRO_FONT* FindOrAddFont(string FontPath, int Size);

private:
     map<FontKey, ALLEGRO_FONT*> FontMap;
};
