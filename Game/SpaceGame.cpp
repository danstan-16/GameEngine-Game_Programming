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

	m_titleFont = new Font();
	m_titleFont->Load("fonts/airstrike.ttf", 64);

	m_titleText = new Text(m_titleFont);
	m_titleText->Create(Engine::Get().GetRenderer(), "XENON", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = new Font();
	m_gameFont->Load("fonts/airstrike.ttf", 32);

	m_scoreText = new Text(m_gameFont);
	m_livesText = new Text(m_gameFont);

	m_gameOverFont = new Font();
	m_gameOverFont->Load("fonts/airstrike.ttf", 64);

	m_gameOverText = new Text(m_gameOverFont);

	Engine::Get().GetAudio().AddSound("explosion", "../../Build/Assets/audio/explosion.mp3");
	Engine::Get().GetAudio().AddSound("pewpew", "../../Build/Assets/audio/pewpew.mp3");
	//Engine::Get().GetAudio().AddSound("theme-music", "../../Build/Assets/audio/theme-music.mp3");


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
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.model = Assets::playerTexture;
	playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
	playerDesc.damping = 3.0f;
	playerDesc.speed = 2000.0f;
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };

	std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
	int model = RandomInt(3);
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	if (model == 0) {
		enemyDesc.model = Assets::enemyModel1;
	}
	else if (model == 1)
	{
		enemyDesc.model = Assets::enemyModel2;
	}
	else
	{
		enemyDesc.model = Assets::enemyModel3;
	}
	
	enemyDesc.transform = Transform{ Vector2{ RandomFloat((float)Engine::Get().GetRenderer().GetWidth()),
												RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 0.0f, 15.0f };
	enemyDesc.speed = 100000.0f;
	enemyDesc.damping = 3.0f;

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
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