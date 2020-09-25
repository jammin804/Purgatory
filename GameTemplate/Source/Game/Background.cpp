#include "Background.h"

#include "Framework/ImageComponent.h"
#include "Framework/SoundComponent.h"

void Background::OnInit()
{
    BackgroundImage = new ImageComponent(this);
    BackgroundMusic = new SoundComponent(this);
}

void Background::OnUpdate()
{
}

void Background::OnShutdown()
{
    delete BackgroundImage;
    BackgroundImage = nullptr;

    delete BackgroundMusic;
    BackgroundMusic = nullptr;
}

void Background::SetImage(string ImagePath)
{
    if (BackgroundImage)
    {
        BackgroundImage->LoadImage(ImagePath);
    }
}

void Background::SetMusic(string MusicPath)
{
    if (BackgroundMusic)
    {
        BackgroundMusic->LoadSample(MusicPath);
        BackgroundMusic->SetLooped(true);
        BackgroundMusic->Play();
    }
}
