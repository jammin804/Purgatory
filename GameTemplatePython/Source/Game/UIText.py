#include "UIText.h"

#include "Framework/TextComponent.h"

void UIText::OnInit()
{
    TextComp = new TextComponent(this);
}

void UIText::OnUpdate()
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
