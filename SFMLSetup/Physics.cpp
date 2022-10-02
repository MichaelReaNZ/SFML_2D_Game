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
	//if (_playerChar->m_invincibleTimeCounter > 0) {

	//	_playerChar->m_invincibleTimeCounter = 0;
	//}
	//
	//if (enabled)
	//{
	//	if (!_playerChar->colliding) {
	//		if (_playerChar->playerVelocityY < 4.0f)
	//		{
	//			_playerChar->playerVelocityY += GravityValue * m_DeltaTime;
	//		}

	//		_playerChar->m_Shape.move(sf::Vector2f(0, _playerChar->playerVelocityY));
	//	}
	//}
}
