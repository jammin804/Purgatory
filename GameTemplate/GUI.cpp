#include "GUI.h"

#include "Framework/ImageComponent.h"
#include "Framework/InputComponent.h"

void GUI::OnInit()
{
	BorderGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
	LifeGUIImageComponent = GameComponent::CreateInstance<ImageComponent>(this);
}

void GUI::OnUpdate(float DeltaTime)
{
}

void GUI::SetBorderGUI(string ImagePath)
{
	if (BorderGUIImageComponent)
	{
		BorderGUIImageComponent->LoadImage(ImagePath);
	}
}

void GUI::SetLifeGUI(string ImagePath)
{
	if (LifeGUIImageComponent)
	{
		LifeGUIImageComponent->LoadImage(ImagePath);
	}
}