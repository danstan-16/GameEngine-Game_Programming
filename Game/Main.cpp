#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Bullet.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <random>

using namespace nu;

int main()
{
    nu::SetWorkingDirectory("Assets"); 
    
    // INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();     

    std::vector<Vector2> points;
    
    // handle events
    bool quit = false;

    while (!quit) {

        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);

        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();

    return 0;
}