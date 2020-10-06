#pragma once

#include "Framework/GameObject.h"

using namespace std;

class TextComponent;

class UIText : public GameObject
{
protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float DeltaTime) override;
    virtual void OnShutdown() override;

public:
    void SetText(string Text);
private:
    TextComponent* TextComp = nullptr;
};

