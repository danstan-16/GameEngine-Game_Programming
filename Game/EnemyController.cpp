#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine.h"

namespace nu
{
	FACTORY_REGISTER(EnemyController)

	void EnemyController::Start()
	{
		Actor::Start();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		assert(m_physicsComponent);
		m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
		assert(m_rendererComponent);

	}

	void EnemyController::Update(float dt)
	{
		if (!m_physicsComponent) Start();
		Vector2 velocity = m_physicsComponent->GetVelocity();

		float dir = 0.0f;
		auto player = m_scene->GetActorByName("PlayerPrototype");
		if (player)
		{
			Vector2 position = GetTransform().position;
			Vector2 playerPosition = player->GetTransform().position;

			if (playerPosition.x < position.x) dir = -1.0f;
			else dir = +1.0f;
		}
		
		if (dir != 0.0f)
		{
			velocity.x = dir * 1000;
			m_rendererComponent->Play("idle");
			// if moving Play("run")
		}
		else
		{
			// else Play("idle")
		}

		m_rendererComponent->SetFlipH(dir < 0.0f);

		m_physicsComponent->SetVelocity(velocity);

		Actor::Update(dt);
	}

	void EnemyController::OnCollision(Actor* other)
	{

	}

	void EnemyController::Read(const json::value_t& value)
	{
		Actor::Read(value);

		JSON_READ_NAME(value, "speed", m_speed);
	}
}