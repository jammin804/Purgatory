#pragma once

#include <allegro5/allegro_font.h>
#include <map>
#include "EString.h"

using namespace std;


namespace Globals
{
    extern ALLEGRO_FONT* DefaultFont;
};

struct FontKey
{
    EString FontPath;
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

public:
    static FontManager* GetInstance();
    ALLEGRO_FONT* FindOrAddFont(EString FontPath, int Size);
	void Init();
	void Shutdown();

private:
    FontManager() = default;

private:
    static FontManager* Instance;
     map<FontKey, ALLEGRO_FONT*> FontMap;
};
