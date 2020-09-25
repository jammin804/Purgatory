#include <stdio.h>
#include "Game/AsteroidsGame.h"

int main()
{
    if (!GameFramework::Init<AsteroidsGame>())
    {
        return 1;
    }

    while (GameFramework::Update())
    {
        continue;
    }

    GameFramework::Shutdown();

    return 0;
}