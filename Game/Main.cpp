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
#include <fstream>
#include <random>

using namespace nu;

int main()
{
    nu::SetWorkingDirectory("Assets");

    //Factory::Instance().Register<Actor>("Actor");
    //Factory::Instance().Register<Actor>("Object");
    //Factory::Instance().Register<Actor>("Player");
    //
    //auto actor = Factory::Instance().Create<Actor>("Actor");
    //std::cout << actor->IsActive() << std::endl;
    //
    //auto object = Factory::Instance().Create<Object>("Object");
    //std::cout << object->IsActive() << std::endl;
    //
    //auto player = Factory::Instance().Create<Player>("Player");
    //std::cout << player->IsActive() << std::endl;
    //
    //json::document_t document;
    //if (json::Load("data/scene.json", document))
    //{
    //    player->Read(document);
    //    std::cout << player->GetName() << std::endl;
    //    std::cout << player->GetTag() << std::endl;
    //
    //    std::cout << player->GetTransform().rotation << std::endl;
    //    std::cout << player->GetSpeed() << std::endl;
    //}
    //
    //
    //// load the json data from a file
    //std::string buffer;
    //if (ReadTextFile("data/data.json", buffer))
    //{
    //    // show the contents of the json file (debug)
    //    std::cout << buffer << std::endl;
    //
    //    // create json document from the json file contents
    //    rapidjson::Document document;
    //    if (json::Load("data/data.json", document))
    //    {
    //        // read the age data (int) from the json
    //        std::string name;
    //        int age;
    //        float speed;
    //        bool isAwake;
    //        nu::Vector2 position;
    //        nu::Vector3 color;
    //
    //        // read the json data
    //        nu::json::Read(document, "name", name);
    //        nu::json::Read(document, "age", age);
    //        nu::json::Read(document, "speed", speed);
    //        nu::json::Read(document, "isAwake", isAwake);
    //        nu::json::Read(document, "position", position);
    //        nu::json::Read(document, "color", color);
    //
    //        // show the data
    //        std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    //        std::cout << position.x << " " << position.y << std::endl;
    //        std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
    //
    //    }
    //}    
    
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