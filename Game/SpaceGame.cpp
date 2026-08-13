#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

using namespace nu;
class Scene;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new nu::Scene();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	json::document_t document;
	if (json::Load("data/scene.json", document))
	{
		std::string type;
		json::Read(document, "type", type);

		auto actor = Factory::Instance().Create<Actor>(type);
	    actor->Read(document);

	    std::cout << actor->GetName() << std::endl;
	    std::cout << actor->GetTag() << std::endl;
	    std::cout << actor->GetTransform().rotation << std::endl;

		Factory::Instance().RegisterPrototype<Actor>("PlayerPrototype", std::move(actor));
	}

	m_titleFont = new Font();
	m_titleFont->Load("fonts/airstrike.ttf", 64);

	m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/airstrike.ttf", 64.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "XENON", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = new Font();
	m_gameFont->Load("fonts/airstrike.ttf", 32);

	m_scoreText = new Text(Resources().GetWithID<Font>("score_font", "fonts/airstrike.ttf", 32.0f));
	m_livesText = new Text(Resources().GetWithID<Font>("lives_font", "fonts/airstrike.ttf", 32.0f));

	m_gameOverFont = new Font();
	m_gameOverFont->Load("fonts/airstrike.ttf", 64);

	m_gameOverText = new Text(Resources().GetWithID<Font>("gameOver_font", "fonts/airstrike.ttf", 64.0f));

	Engine::Get().GetAudio().AddSound("explosion", "../../Build/Assets/audio/explosion.mp3");
	Engine::Get().GetAudio().AddSound("pewpew", "../../Build/Assets/audio/pewpew.mp3");


	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case SpaceGame::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = SpaceGame::StartGame;
		}
		break;

	case SpaceGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_spawnTime = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = SpaceGame::StartLevel;
		break;

	case SpaceGame::StartLevel:
		m_scene->RemoveAllActors();
		SpawnPlayer();
		m_spawnTime = 5.0f;
		m_gameState = SpaceGame::GamePlay;
		break;

	case SpaceGame::GamePlay:
		//Engine::Get().GetAudio().PlaySound("theme-music");
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTimer = m_spawnTime;
			SpawnEnemy();
			m_spawnCount++;
			if (m_spawnCount > 5)
			{
				m_spawnCount = 0;
				m_spawnTime -= 0.5f;
			}
		}
		break;
	case SpaceGame::GameOver:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_scene->RemoveAllActors();
			m_gameState = SpaceGame::Title;
		}
		break;

	default:
		break;
	}

	Game::Update(dt);
}


void SpaceGame::Draw(nu::Renderer& renderer)
{
	switch (m_gameState)
	{
	case SpaceGame::Title:
		// draw title
		m_titleText->Draw(renderer, renderer.GetWidth() - 750, renderer.GetHeight() - 800);
		break;

	case SpaceGame::StartGame:
		break;
	case SpaceGame::StartLevel:
		break;
	case SpaceGame::GamePlay:
		// draw score / lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30, 30);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, renderer.GetWidth() - 200, 30);
		break;

	case SpaceGame::GameOver:
		// draw gameover
		m_gameOverText->Create(renderer, "GAME OVER", { 1.0f, 0.0f, 0.0f });
		m_gameOverText->Draw(renderer, renderer.GetWidth() - 850, renderer.GetHeight() - 900);
		break;
	default:
		break;
	}

	Game::Draw(renderer);
}

void SpaceGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy()
{
	int model = RandomInt(3);

	if (model == 0) {
		auto actor = Factory::Instance().Create<Actor>("Enemy01");
		m_scene->AddActor(std::move(actor));
	}
	else if (model == 1)
	{
		auto actor = Factory::Instance().Create<Actor>("Enemy02");
		m_scene->AddActor(std::move(actor));
	}
	else
	{
		auto actor = Factory::Instance().Create<Actor>("Enemy03");
		m_scene->AddActor(std::move(actor));
	}
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;
	if (m_lives == 0)
	{
		m_gameState = SpaceGame::GameOver;
	}
	else m_gameState = SpaceGame::StartLevel;
}