#include "UIText.h"

#include "Framework/TextComponent.h"

void UIText::OnInit()
{
    TextComp = new TextComponent(this);
}

void UIText::OnUpdate(float DeltaTime)
{

}

void UIText::OnShutdown()
{
    delete TextComp;
    TextComp = nullptr;
}

void UIText::SetText(string Text)
{
    if (TextComp)
    {
        TextComp->SetText(Text);
    }
}
