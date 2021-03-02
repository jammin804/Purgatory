#include "GUI.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"
#include "Framework/TextComponent.h"

void GUI::OnInit()
{
	LifeGUITextComponent = GameComponent::CreateInstance<TextComponent>(this);
	LayerGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	LifeGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	BorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	AmountOfHealthText = GameComponent::CreateInstance<TextComponent>(this);
	

	FearLayerGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	FearGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	FearBorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	FearGUITextComponent = GameComponent::CreateInstance<TextComponent>(this);
	AmountOfFearText = GameComponent::CreateInstance<TextComponent>(this);

	CoinGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	CoinGUITextComponent = GameComponent::CreateInstance<TextComponent>(this);
	//CoinFont = GameComponent::CreateInstance<FontManager>(this);
}

void GUI::OnPostInit()
{
	

	LayerGUIImageComponent->SetScaleFromLeft(true);
	LayerGUIImageComponent->SetScale(MAX_LIFESCALE);
	LayerGUIImageComponent->SetOffsetX(100.0f);
	LifeGUIImageComponent->SetScaleFromLeft(true);
	LifeGUIImageComponent->SetScaleX(MAX_LIFESCALE);
	LifeGUIImageComponent->SetScaleY(MAX_LIFESCALE);
	LifeGUIImageComponent->SetOffsetX(100.0f);
	BorderGUIImageComponent->SetScaleFromLeft(true);
	BorderGUIImageComponent->SetScale(MAX_LIFESCALE);
	BorderGUIImageComponent->SetOffsetX(100.0f);

	LifeGUITextComponent->SetOffsetY(-10.0f);
	LifeGUITextComponent->SetOffsetX(50.0f);
	LifeGUITextComponent->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	LifeGUITextComponent->SetText("Health");


	FearLayerGUIImageComponent->SetScaleFromLeft(true);
	FearLayerGUIImageComponent->SetScale(MAX_LIFESCALE);
	FearLayerGUIImageComponent->SetOffsetY(30.0f);
	FearLayerGUIImageComponent->SetOffsetX(100.0f);
	FearGUIImageComponent->SetScaleFromLeft(true);
	FearGUIImageComponent->SetOffsetY(30.0f);
	FearGUIImageComponent->SetScaleX(MAX_LIFESCALE);
	FearGUIImageComponent->SetScaleY(MAX_LIFESCALE);
	FearGUIImageComponent->SetOffsetX(100.0f);
	FearBorderGUIImageComponent->SetScaleFromLeft(true);
	FearBorderGUIImageComponent->SetScale(MAX_LIFESCALE);
	FearBorderGUIImageComponent->SetOffsetY(30.0f);
	FearBorderGUIImageComponent->SetOffsetX(100.0f);

	FearGUITextComponent->SetOffsetY(20.0f);
	FearGUITextComponent->SetOffsetX(40.0f);
	FearGUITextComponent->SetFont("Fonts/Boxy-Bold.ttf", FontSize);
	FearGUITextComponent->SetText("Fear");

	CoinGUIImageComponent->SetScaleFromLeft(true);
	CoinGUIImageComponent->SetOffsetY(60.0f);
	CoinGUIImageComponent->SetScale(2.0f);
	CoinGUITextComponent->SetOffsetY(60.0f);
	CoinGUITextComponent->SetOffsetX(50.0f);
	CoinGUITextComponent->SetFont("Fonts/Boxy-Bold.ttf", FontSize);

}

void GUI::OnUpdate(float DeltaTime)
{
	if (player)
	{

		SetLifePercentage(player->GetLivesLeft()/static_cast <float>(player->GetMaxLivesLeft()));

		char CoinsCollected[10];
		sprintf_s(CoinsCollected, "X %d", player->GetNumberOfCoins());
		CoinGUITextComponent->SetText(CoinsCollected);

		/*char HealthLeft[50];
		sprintf_s(HealthLeft,"")*/
		AmountOfHealthText->SetText(player->GetLivesLeft() + "/" + player->GetMaxLivesLeft());
		AmountOfHealthText->SetOffset(500, 100);
	}
}

void GUI::SetLifePercentage(float PercentageLife)
{
	LifeGUIImageComponent->SetScaleX(MAX_LIFESCALE * PercentageLife);
}

void GUI::SetFearPercentage(float FearPercentageLife)
{
	//Reduce fear based on the in-game time
	FearGUIImageComponent->SetScaleX(MAX_LIFESCALE * FearPercentageLife);
}

void GUI::SetBorderImage(string ImagePath)
{
	if (BorderGUIImageComponent)
	{
		BorderGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetLayerImage(string ImagePath)
{
	if (LayerGUIImageComponent)
	{
		LayerGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetLifeImage(string ImagePath)
{
	if (LifeGUIImageComponent)
	{
		LifeGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetFearLayerImage(string ImagePath)
{
	if (FearLayerGUIImageComponent)
	{
		FearLayerGUIImageComponent->LoadImage(ImagePath);
	}

}

void GUI::SetFearImage(string ImagePath)
{
	if (FearGUIImageComponent)
	{
		FearGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetFearBorderImage(string ImagePath)
{
	if (FearBorderGUIImageComponent)
	{
		FearBorderGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetCoinImage(string ImagePath)
{
	if (CoinGUIImageComponent)
	{
		CoinGUIImageComponent->LoadImage(ImagePath);
	}

}

/*void GUI::UpdateFearRemaining(int NewTimeMins, int NewTimeSeconds)
{
	FearGUIImageComponent->SetScaleX(FearRemaining * PercentageLife);
}*/
