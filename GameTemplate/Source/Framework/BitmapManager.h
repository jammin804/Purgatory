#pragma once

#include <allegro5/bitmap.h>
#include <string>
#include <map>

using namespace std;

struct SBitmapCache
{
    ALLEGRO_BITMAP* ImageBitmap = nullptr;
    int ImageWidth = 0;
    int ImageHeight = 0;
};

class BitmapManager
{
    friend class GameFramework;
    void Init();
    void Shutdown();
public:
    SBitmapCache* FindOrAddBitmap(string BitmapPath);

private:
     map<string, SBitmapCache> BitmapMap;
};
