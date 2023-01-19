#include <stdio.h>
#include "Game/PurgatoryGame.h"

int main()
{
    if (!GameFramework::Init<PurgatoryGame>())
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