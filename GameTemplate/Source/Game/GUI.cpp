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
	LifeGUIImageComponent->SetScaleX(2.0f);
	LifeGUIImageComponent->SetScaleY(2.0f);
	BorderGUIImageComponent->SetScaleFromLeft(true);
	BorderGUIImageComponent->SetScale(2.0f);
	FearGUIImageComponent->SetScaleFromLeft(true);
	FearGUIImageComponent->SetScaleX(2.0f);
	FearGUIImageComponent->SetScaleY(2.0f);
	FearBorderGUIImageComponent->SetScaleFromLeft(true);
	FearBorderGUIImageComponent->SetScale(2.0f);
}

void GUI::OnUpdate(float DeltaTime)
{
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
