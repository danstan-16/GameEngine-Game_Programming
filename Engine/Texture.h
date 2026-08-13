#pragma once
#include <iostream>
#include "Vector2.h"

struct SDL_Texture;

namespace nu
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		Vector2 GetSize() const
		{
			return m_size;
		}

		friend class Renderer;
		SDL_Texture* m_texture{ nullptr };

	private:
		Vector2 m_size{ 0.0f, 0.0f };
	};
}
