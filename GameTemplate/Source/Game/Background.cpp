#include "Background.h"

#include "Framework/ImageComponent.h"
#include "Framework/SoundComponent.h"

void Background::OnInit()
{
	for (int i = 0; i < 9; i++)
	{
		BackgroundImage[i] = GameComponent::CreateInstance<ImageComponent>(this);
	}
 
	WallVImage = GameComponent::CreateInstance<ImageComponent>(this);
    BackgroundMusic = GameComponent::CreateInstance<SoundComponent>(this);
}

void Background::OnPostInit()
{
	int row = 0;
	int column = 0;
	for (int i = 0; i < 9; i++)
	{
		row = i / 3;
		column = i % 3;
		if (BackgroundImage[i])
		{
			float x = -2560.0f + row * 2560.0f + Globals::WindowSizeX * 0.5f;
			float y = -1440.0f + column * 1440.0f + Globals::WindowSizeY * 0.5f;
			BackgroundImage[i]->SetOffset(x, y);
		}
	}

}

void Background::OnUpdate(float DeltaTime)
{
}

void Background::SetImage(string ImagePath)
{
	for (int i = 0; i < 9; i++)
	{
		if (BackgroundImage[i])
		{
			BackgroundImage[i]->LoadImage(ImagePath);
		}
	}
}

void Background::SetWallVImage(string ImagePath)
{
	if (WallVImage)
	{
		WallVImage->LoadImage(ImagePath);
	}

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
