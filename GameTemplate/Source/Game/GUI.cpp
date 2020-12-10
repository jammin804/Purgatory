#include "GUI.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"

void GUI::OnInit()
{
	LifeGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	BorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	FearGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	FearBorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
}

void GUI::OnPostInit()
{
	LifeGUIImageComponent->SetScaleFromLeft(true);
	LifeGUIImageComponent->SetScaleX(MAX_LIFESCALE);
	LifeGUIImageComponent->SetScaleY(MAX_LIFESCALE);
	BorderGUIImageComponent->SetScaleFromLeft(true);
	BorderGUIImageComponent->SetScale(MAX_LIFESCALE);
	FearGUIImageComponent->SetScaleFromLeft(true);
	FearGUIImageComponent->SetOffsetY(30.0f);
	FearGUIImageComponent->SetScaleX(MAX_LIFESCALE);
	FearGUIImageComponent->SetScaleY(MAX_LIFESCALE);
	FearBorderGUIImageComponent->SetScaleFromLeft(true);
	FearBorderGUIImageComponent->SetScale(MAX_LIFESCALE);
	FearBorderGUIImageComponent->SetOffsetY(30.0f);
}

void GUI::OnUpdate(float DeltaTime)
{
	if (player)
	{
		SetLifePercentage(player->GetLivesLeft()/static_cast <float>(player->GetMaxLivesLeft()));
	}
}

void GUI::SetLifePercentage(float PercentageLife)
{
	LifeGUIImageComponent->SetScaleX(MAX_LIFESCALE * PercentageLife);
}

void GUI::SetFearPercentage(float FearPercentageLife)
{
	//Reduce fear based on the in-game time
}

void GUI::SetBorderImage(string ImagePath)
{
	if (BorderGUIImageComponent)
	{
		BorderGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetLifeImage(string ImagePath)
{
	if (LifeGUIImageComponent)
	{
		LifeGUIImageComponent->LoadImage(ImagePath);
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
