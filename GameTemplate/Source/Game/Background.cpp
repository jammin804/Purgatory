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
	if (BackgroundImage)
	{
		BackgroundImage->SetOffset(638.0f, 360.0f);
	}
}

void Background::OnUpdate(float DeltaTime)
{
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
        //BackgroundMusic->Play();
		BackgroundMusic->Stop(); //For testing
    }
}
