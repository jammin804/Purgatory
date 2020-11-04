#include "GUI.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"

void GUI::OnInit()
{
	BorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	LifeGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
}

void GUI::OnPostInit()
{

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