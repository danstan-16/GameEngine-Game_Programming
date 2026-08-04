#include "Assets.h"

using namespace nu;

namespace Assets
{
	Mesh body{{
			Vector2{2, 0},
			Vector2{0, 1},
			Vector2{-3, 3},
			Vector2{-1, 0 },
			Vector2{-3, -3},
			Vector2{0, -1},
			Vector2{2, 0}
			},
			Color {0.0f, 255.0f, 0.0f} 
			};

	Model playerModel{ std::vector<Mesh>{body} };

	Mesh enemyBody1{ {
			Vector2{2, 0},
			Vector2{0, 1},
			Vector2{-3, 3},
			Vector2{-1, 0 },
			Vector2{-3, -3},
			Vector2{0, -1},
			Vector2{2, 0}
			},
			Color {255.0f, 255.0f, 255.0f}
	};

	Model enemyModel1{ std::vector<Mesh>{enemyBody1} };

	Mesh enemyBody2{ {
			Vector2{2, 0},
			Vector2{0, 1},
			Vector2{-3, 1},
			Vector2{-1, 0 },
			Vector2{-3, -1},
			Vector2{0, -1},
			Vector2{2, 0}
			},
			Color {255.0f, 255.0f, 255.0f}
	};

	Model enemyModel2{ std::vector<Mesh>{enemyBody2} };

	Mesh enemyBody3{ {
			Vector2{2, 0},
			Vector2{0, 1},
			Vector2{-2, 1},
			Vector2{-1, 0 },
			Vector2{-2, -1},
			Vector2{0, -1},
			Vector2{2, 0}
			},
			Color {255.0f, 255.0f, 255.0f}
	};

	Model enemyModel3{ std::vector<Mesh>{enemyBody3} };

	Mesh bulletMesh{ {
			Vector2{ -1, -1 },
			Vector2{ 1, 0 },
			Vector2{ -1, 1 },
			Vector2{ -1, -1 },
			},
			Color{ 0.0f, 240.0f, 0.0f }
	};
	Model bulletModel{ std::vector<Mesh>{bulletMesh} };
}