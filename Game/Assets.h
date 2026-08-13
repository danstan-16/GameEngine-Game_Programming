#pragma once
#include "Model.h"
#include "Texture.h"
#include <memory>

namespace Assets
{
	class Assets 
	{
	public:
		std::shared_ptr<nu::Texture> GetPlayerTexture();
	};
	extern std::shared_ptr<nu::Model> playerTexture;
	extern std::shared_ptr<nu::Model> enemyModel1;
	extern std::shared_ptr<nu::Model> enemyModel2;
	extern std::shared_ptr<nu::Model> enemyModel3;
	extern std::shared_ptr<nu::Model> bulletModel;
}