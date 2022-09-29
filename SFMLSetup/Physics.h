#pragma once
#include "Character.h"
class Physics
{
public:
	float GravityValue = 10.0f;
	sf::Clock GlobalClock;
	float m_DeltaTime = 0.0f;

	Physics();
	~Physics();

	void PhysicsUpdate();

	void UpdateDynamicObject(Character* _playerChar, bool enabled);
};

