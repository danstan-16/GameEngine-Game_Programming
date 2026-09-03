#**My Game Engine**

A component-based 2D game engine built in C++20, designed around modular systems for rendering, audio, input, physics, and game object management.
The engine also includes DRUIA, a demo game that showcases the engine's features and demonstrates how its systems can be used to build a complete game.

##Features
###Component-Based Architecture
- Modular actors and components
- Flexible composition of game objects
- Systems designed to work independently
- 
###Rendering System
- 2D rendering
- Sprite and game object rendering
- Tilemap support
- UI rendering
- 
###Audio System
- Powered by FMOD
- Sound effect and music playback
- Centralized audio management
- 
###Input System
- Keyboard and controller input
- Centralized input handling
- Game-specific input mapping
- 
###Physics System
- Powered by Box2D
- 2D collision detection
- Rigid body physics
- Physics-driven components
- 
###Serialization
- Powered by RapidJSON
- Game data serialization
- Component and actor data persistence
- 
###Demo Game — DRUIA
- Demonstrates the engine in a complete game environment
- Actors
- Components
- Tilemaps
- UI
- Audio
- Physics
- Rendering

##Technology
###Technology			###Purpose
C++20					Core programming language
SDL3					Windowing, input, and platform functionality
FMOD					Audio and sound management
Box2D					2D physics and collision
RapidJSON				Serialization and data management