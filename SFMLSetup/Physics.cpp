#include "Physics.h"

Physics::Physics()
{
}

Physics::~Physics()
{
}

void Physics::PhysicsUpdate()
{
	m_DeltaTime = GlobalClock.getElapsedTime().asSeconds();
	GlobalClock.restart();
}

void Physics::UpdateDynamicObject(Character* _playerChar, bool enabled)
{
}
