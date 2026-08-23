#pragma once

#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"
#include "File.h"

#include "Text.h"
#include "Texture.h"

#include "ResourceManager.h"
#include "Resource.h"

#include "Json.h"
#include "StringUtils.h"

#include "Factory.h"

#include "Physics/Physics.h"

//systems
#include "Random.h"
#include "Input.h"
#include "GameTime.h"
#include "Audio.h"
#include "ParticleSystem.h"

// framework
#include "Actor.h"
#include "Scene.h"
#include "Game.h"

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput()
		{
			return m_input;
		}
		Renderer& GetRenderer()
		{
			return m_renderer;
		}
		Time& GetTime()
		{
			return m_time;
		}

		Audio& GetAudio()
		{
			return m_audio;
		}

		ParticleSystem& GetPS() { return m_particleSystem; }
		Physics& GetPhysics() { return m_physics; }


	private:
		Engine() = default;

		ParticleSystem m_particleSystem;
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		Physics m_physics;

	};
}
