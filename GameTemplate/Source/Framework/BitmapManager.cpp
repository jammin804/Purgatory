#include "BitmapManager.h"
#include <allegro5/bitmap_io.h>

void BitmapManager::Init()
{
}

void BitmapManager::Shutdown()
{
    for (auto KeyPair : BitmapMap)
    {
        al_destroy_bitmap(KeyPair.second.ImageBitmap);
    }
    BitmapMap.clear();
}

SBitmapCache* BitmapManager::FindOrAddBitmap(string BitmapPath)
{
    auto iter = BitmapMap.find(BitmapPath);
    if (iter != BitmapMap.end())
    {
        return &(iter->second);
    }

    ALLEGRO_BITMAP* Image = al_load_bitmap(BitmapPath.c_str());
    if (Image)
    {
        SBitmapCache NewBitmapCache;
        NewBitmapCache.ImageBitmap = Image;
        NewBitmapCache.ImageWidth = al_get_bitmap_width(Image);
        NewBitmapCache.ImageHeight = al_get_bitmap_height(Image);
        BitmapMap.insert(pair<string, SBitmapCache>(BitmapPath, NewBitmapCache));
        return FindOrAddBitmap(BitmapPath);
    }
    return nullptr;
}

