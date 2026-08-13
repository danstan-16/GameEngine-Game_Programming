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

using namespace nu;

int main()
{
    //Factory::Instance().Register<Actor>("Actor");
    //
    nu::SetWorkingDirectory("Assets");
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
    //        int age;
    //        json::Read(document, "age", age);
    //        // show the age data
    //        std::cout << age << std::endl;
    //    }
    //}
    //
    //+ After running the program, the console will display the contents of the** JSON** file and the** age** data.
    //    <div align = "left">
    //    <img src = "json-output.jpg" alt = "Output" width = "80%" / >
    //    < / div>
    //
    //    ### Add Addition JSON Functions ###
    //    _Add additional functions to load different data types from the * *JSON * *file._
    //
    //    + In the Json.h file, _add_ the following functions.
    //    + Add new functions to load * *float**, **bool**, **std::string**, ** vec2**, and **vec3**
    //    +Include * *Math / Vector2.h * *and **Math / Vector3.h**
    //
    //// read/show the data from the json file
    //std::string name;
    //int age;
    //float speed;
    //bool isAwake;
    //nu::Vector2 position;
    //nu::Vector3 color;
    //
    //// read the json data
    //nu::json::Read(document, "name", name);
    //nu::json::Read(document, "age", age);
    //nu::json::Read(document, "speed", speed);
    //nu::json::Read(document, "isAwake", isAwake);
    //nu::json::Read(document, "position", position);
    //nu::json::Read(document, "color", color);
    //
    //// show the data
    //std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    //std::cout << position.x << " " << position.y << std::endl;
    //std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
    //
    //{
    //    std::string name;
    //    int score;
    //    bool isAlive;
    //
    //    //save game data
    //    bool save = false;
    //    if (save)
    //    {
    //        name = "Danielle Shelby";
    //        score = 1234;
    //        isAlive = true;
    //
    //       
    //        std::ofstream file("data/game.txt", std::ios::app);
    //        if (file.is_open())
    //        {
    //            file << name << "\n";
    //            file << score << "\n";
    //            file << std::boolalpha << isAlive << "\n";
    //        }
    //    }
    //
    //    // load game data
    //    bool load = true;
    //    if (load)
    //    {
    //        std::ifstream file("data/game.txt");
    //        if (file.is_open())
    //        {
    //            std::getline(file, name);
    //
    //            std::string str;
    //            std::getline(file, str);
    //
    //            score = std::stoi(str);
    //            file >> std::boolalpha >> isAlive;
    //        }
    //    }
    //
    //    // display game data
    //    std::cout << name << std::endl;
    //    std::cout << score << std::endl;
    //    std::cout << std::boolalpha << isAlive << std::endl;
    //}

    // INITIALIZATION
    Engine::Get().Initialize();

    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/space_background.jpg", Engine::Get().GetRenderer());

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

        Engine::Get().GetRenderer().DrawTexture(texture.get(), 300, 300);

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();

    return 0;
}