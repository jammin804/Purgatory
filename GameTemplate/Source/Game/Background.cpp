#include "Background.h"

#include "Framework/ImageComponent.h"
#include "Framework/SoundComponent.h"

void Background::OnInit()
{
	BackgroundImage = GameComponent::CreateInstance<ImageComponent>(this);
    BackgroundMusic = GameComponent::CreateInstance<SoundComponent>(this);
}

void Background::OnPostInit()
{
	BackgroundImage->SetTilingU(10);
	BackgroundImage->SetTilingV(10);
    BackgroundImage->SetOffset(-3000, -2000);
}

void Background::OnUpdate(float DeltaTime)
{
}

void Background::SetImage(string ImagePath)
{
	BackgroundImage->LoadImage(ImagePath);
}

void Background::SetMusic(string MusicPath)
{
    if (BackgroundMusic)
    {
        BackgroundMusic->LoadSample(MusicPath);
        BackgroundMusic->SetLooped(true);
        BackgroundMusic->Play();
		BackgroundMusic->Stop(); //For testing
    }
}
