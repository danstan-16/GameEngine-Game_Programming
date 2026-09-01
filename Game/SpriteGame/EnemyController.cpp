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
		Vector2 velocity = m_physicsComponent->GetVelocity();

		float dir = 0.0f;
		
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
	}
}