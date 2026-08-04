#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "fmod.hpp"
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) {
        std::cout << "assignment\n";
        return *this;
    }
};

int main()
{
    std::cout << "=============object==============\n";

    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }

    std::cout << "=============raw pointers============\n";

    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
        //delete objectC;

    }

    std::cout << "=============smart pointers==============\n";

    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectA.get() << std::endl; // the 'guts' are ripped out and given to B
        std::cout << objectB.get() << std::endl;
    }

    return 0;

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