#include "pch.h"
#include <iostream>
#include "GameEngine.h"

int main()
{
    GameEngine game;

    while (game.GetWindowOpen())
    {
        //Delta time();
        //Update();
        game.UpdateDeltaTime();
        game.Render();
        game.Update();
    }

    return 0;
}
