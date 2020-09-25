#pragma once

class GameObject;

class GameComponent
{
    friend class GameObject;

public:
    GameComponent(GameObject* GOOwner);
    virtual ~GameComponent(){}

    void SetOffsetX(float NewOffsetX) { OffsetX = NewOffsetX; }
    void SetOffsetY(float NewOffsetY) { OffsetY = NewOffsetY; }
    void SetOffset(float NewOffsetX, float NewOffsetY) { SetOffsetX(NewOffsetX); SetOffsetY(NewOffsetY); }

    float GetOffsetX() const { return OffsetX; }
    float GetOffsetY() const { return OffsetY; }

protected:   
    virtual void OnInit() = 0;

    virtual void OnUpdate() = 0;

    virtual void OnRender() {}

    virtual void OnShutdown() {}

    const GameObject* GetOwner() const { return Owner; }

private:
    void Init();
    void Update();
    void Shutdown();
    void Render();

    GameObject* Owner = nullptr;

    float OffsetX = 0.0f;
    float OffsetY = 0.0f;
};

