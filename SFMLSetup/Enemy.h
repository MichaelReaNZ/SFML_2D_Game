#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"


class Enemy
{
	sf::Vector2f m_Position;
	sf::Texture* m_texture;
public:
	sf::RectangleShape m_Shape;

	float m_MoveSpeed = 6.0f;
	sf::Vector2i m_MoveVec = sf::Vector2i(0, 0);
	float m_ShootSpeed = 6.0f;

	sf::Clock m_WalkingTimeClock;
	sf::Clock m_ShootFrequencyClock;
	int m_ShootFrequency;

	void ChangeDirectionRandomly();
	Bullet* ShootBullet(sf::Vector2f _EnemyPosition, sf::Vector2f _CharacterPosition);

	Enemy(sf::Vector2f _Position);
	~Enemy();
	void Update(sf::RenderWindow& _Window);
};

